
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_util_concurrent_locks_ReentrantReadWriteLock__
#define __java_util_concurrent_locks_ReentrantReadWriteLock__

#pragma interface

#include <java/lang/Object.h>

class java::util::concurrent::locks::ReentrantReadWriteLock : public ::java::lang::Object
{

public:
  ReentrantReadWriteLock();
  ReentrantReadWriteLock(jboolean);
  virtual ::java::util::concurrent::locks::ReentrantReadWriteLock$WriteLock * target$writeLock();
  virtual ::java::util::concurrent::locks::ReentrantReadWriteLock$ReadLock * target$readLock();
  virtual jboolean isFair();
public: // actually protected
  virtual ::java::lang::Thread * getOwner();
public:
  virtual jint getReadLockCount();
  virtual jboolean isWriteLocked();
  virtual jboolean isWriteLockedByCurrentThread();
  virtual jint getWriteHoldCount();
  virtual jint getReadHoldCount();
public: // actually protected
  virtual ::java::util::Collection * getQueuedWriterThreads();
  virtual ::java::util::Collection * getQueuedReaderThreads();
public:
  virtual jboolean hasQueuedThreads();
  virtual jboolean hasQueuedThread(::java::lang::Thread *);
  virtual jint getQueueLength();
public: // actually protected
  virtual ::java::util::Collection * getQueuedThreads();
public:
  virtual jboolean hasWaiters(::java::util::concurrent::locks::Condition *);
  virtual jint getWaitQueueLength(::java::util::concurrent::locks::Condition *);
public: // actually protected
  virtual ::java::util::Collection * getWaitingThreads(::java::util::concurrent::locks::Condition *);
public:
  virtual ::java::lang::String * toString();
  virtual ::java::util::concurrent::locks::Lock * readLock();
  virtual ::java::util::concurrent::locks::Lock * writeLock();
public: // actually package-private
  static ::java::util::concurrent::locks::ReentrantReadWriteLock$Sync * access$2(::java::util::concurrent::locks::ReentrantReadWriteLock *);
private:
  static const jlong serialVersionUID = -6992448646407690164LL;
  ::java::util::concurrent::locks::ReentrantReadWriteLock$ReadLock * __attribute__((aligned(__alignof__( ::java::lang::Object)))) readerLock;
  ::java::util::concurrent::locks::ReentrantReadWriteLock$WriteLock * writerLock;
  ::java::util::concurrent::locks::ReentrantReadWriteLock$Sync * sync;
public:
  static ::java::lang::Class class$;
};

#endif // __java_util_concurrent_locks_ReentrantReadWriteLock__
