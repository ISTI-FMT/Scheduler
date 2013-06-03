#include "EventQueue.h"


EventQueue::EventQueue(void)
{
	queueEvent= gcnew ConcurrentQueue<Event^>();
}


  void EventQueue::Subscribe(IObservable<Event^> ^provider)
   {
      if (provider != nullptr) 
         unsubscriber = provider->Subscribe(this);
   }

    void EventQueue::OnCompleted()
   {
      Console::WriteLine("The Location Tracker has completed transmitting data to");
      Unsubscribe();
   }

   void EventQueue::OnError(Exception ^e)
   {
      Console::WriteLine(" The location cannot be determined.");
   }

    void EventQueue::OnNext(Event^ value)
   {
      queueEvent->Enqueue(value);
   }

    void EventQueue::Unsubscribe()
   {
      delete unsubscriber;
   }