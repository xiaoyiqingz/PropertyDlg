2015年4月16日16:54:40
  add mfc  worker thread and ui thread 
  worker thread : Thread.h  Thread.cpp 
    1.worker thread has packaged in a class

  UI  thread:UIThread.h  UIThread.cpp   
  	1.inherit the CWinThread, and if you want to send a message to this thread(without Dialog), should postthreadmessage, and  message loop macro use ON_THREAD_MESSAGE instead of ON_MESSAGE  
	2,remember to  postmessage(wm_quit) or destroywindow when you want to end this ui message loop 

(Remaining problem: there are to many thread when app run, should know what are they)	
