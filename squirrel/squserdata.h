/*  see copyright notice in squirrel.h */
#pragma once

#include "sqobject.h"
#include "sqstate.h"
#include "sqvm.h"

#include <new>

struct SQUserData : SQDelegable {
	SQUserData(SQSharedState *ss) {
		_delegate = nullptr;
		_hook = nullptr;
		INIT_CHAIN();
		ADD_TO_CHAIN(&_ss(this)->_gc_chain, this);
	}
	~SQUserData() {
		REMOVE_FROM_CHAIN(&_ss(this)->_gc_chain, this);
		SetDelegate(nullptr);
	}
	static SQUserData *Create(SQSharedState *ss, SQInteger size) {
		SQUserData *ud = static_cast<SQUserData *>(SQ_MALLOC(sq_aligning(sizeof(SQUserData)) + size));
		new (ud) SQUserData(ss);
		ud->_size = size;
		ud->_typetag = nullptr;
		return ud;
	}
#ifndef NO_GARBAGE_COLLECTOR
	void Mark(SQCollectable **chain);
	void Finalize() { SetDelegate(nullptr); }
	SQObjectType GetType() { return OT_USERDATA; }
#endif
	void Release() {
		if (_hook != nullptr) {
			_hook((SQUserPointer)sq_aligning(this + 1), _size);
		}
		SQInteger tsize = _size;
		this->~SQUserData();
		SQ_FREE(this, sq_aligning(sizeof(SQUserData)) + tsize);
	}

	SQInteger _size;
	SQRELEASEHOOK _hook;
	SQUserPointer _typetag;
	//SQChar _val[1];
};
