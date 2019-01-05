#include "Publisher.h"
#include "Observer.h"
#include "Exception.h"


#include <sstream>
#include <set>
#include <unordered_map>


using std::string;
using std::vector;
using std::set;
using std::ostringstream;
using std::unique_ptr;
using std::shared_ptr;



namespace mydesign
{

	class Publisher::PublisherImpl
	{
		using observersList =  std::unordered_map<string, unique_ptr<Observer>> ;
		using Events = std::unordered_map<string, observersList>;


		public:
			PublisherImpl();
			~PublisherImpl();

			void attach(const string& eventName, unique_ptr<Observer> observer);
		    unique_ptr<Observer> detach(const string& eventName, const string& observer);
		    void notify(const string& eventName, shared_ptr<EventData> d) const;
		    void registerEvent(const string& eventName);
		    void registerEvents(const vector<string>& eventNames);
		    set<string> listEvents() const;
		    set<string> listEventObservers(const string& eventName) const;
    
		    Events::const_iterator findCheckedEvent(const string& eventName) const;
			Events::iterator findCheckedEvent(const string& eventName);	

		private:
			Events events_;

	};


	Publisher::PublisherImpl::PublisherImpl()
	{

	}
	Publisher::PublisherImpl::~PublisherImpl()
	{
		
	}

  Publisher::PublisherImpl::Events::const_iterator Publisher::PublisherImpl::findCheckedEvent(const string& eventName) const
  {
  	auto ev = events_.find(eventName);

  	if(ev == events_.end())
  	{
  		
  	}

  	return ev;

  }


	Publisher::PublisherImpl::Events::iterator Publisher::PublisherImpl::findCheckedEvent(const string &eventName)
	{
	    auto ev = events_.find(eventName);
	    if( ev == events_.end() )
	    {
	        ostringstream oss;
	        oss << "Publisher does not support event '" << eventName << "'";
	        throw Exception( oss.str() );
	    }

	    return ev;
	}


	void Publisher::PublisherImpl::attach(const string& eventName, unique_ptr<Observer> observer)
	{ 
	    auto ev = findCheckedEvent(eventName);   
	    auto& obsList = ev->second;
	    
	    auto obs = obsList.find(observer->name());
	    if( obs != obsList.end() )
	        throw Exception("Observer already attached to publisher");   

	    obsList.insert( std::make_pair(observer->name(), std::move(observer)) );
	    
	    return;
	}

	unique_ptr<Observer> Publisher::PublisherImpl::detach(const string& eventName, const string& observer)
	{ 
	    auto ev = findCheckedEvent(eventName);
	    auto& obsList = ev->second;
	    
	    auto obs = obsList.find(observer);
	    if( obs == obsList.end() )
	        throw Exception("Cannot detach observer because observer not found");
	    
	    auto tmp = std::move(obs->second);
	    obsList.erase(obs);
	    
	    return tmp;
	}



	void Publisher::PublisherImpl::notify(const string& eventName, shared_ptr<EventData> d) const
	{
	    auto ev = findCheckedEvent(eventName);
	    const auto& obsList = ev->second;
	    
	    for(const auto& obs : obsList)
	        obs.second->notify(d);
	    
	    return;
	}

	void Publisher::PublisherImpl::registerEvent(const string& eventName)
	{ 
	    auto i = events_.find(eventName);
	    if( i != events_.end() )
	        throw Exception{"Event already registered"};
	    
	    events_[eventName] = observersList{};
	  
	    return;
	}

	void Publisher::PublisherImpl::registerEvents(const vector<string>& eventNames)
	{ 
	    for(auto i : eventNames)  
	        registerEvent(i);
	  
	    return;
	}

	set<string> Publisher::PublisherImpl::listEvents() const
	{
	    set<string> tmp;
	    for(const auto& i : events_)
	        tmp.insert(i.first);

	    
	    return tmp;
	}
	    
	set<string> Publisher::PublisherImpl::listEventObservers(const string& eventName) const
	{
	    auto ev = findCheckedEvent(eventName);

	    set<string> tmp;
	    for(const auto& kvp : ev->second)
	        tmp.insert(kvp.first);

	    return tmp;
	}


	Publisher::Publisher()
	{
		publisherImpl_ = std::make_unique<PublisherImpl>();
	}

	Publisher::~Publisher()
	{

	}

	void Publisher::attach(const string& eventName, unique_ptr<Observer> observer)
	{
		publisherImpl_->attach(eventName, std::move(observer));
		return;
	}


	unique_ptr<Observer> Publisher::detach(const string& eventName, const string& observer)
	{
    	return publisherImpl_->detach(eventName,observer);
	}


	void Publisher::raise(const string& eventName, std::shared_ptr<EventData> d) const
	{
		publisherImpl_->notify(eventName,d);
		return;
	}


	void Publisher::registerEvent(const string& eventName)
	{
	    publisherImpl_->registerEvent(eventName);
	    return;
	}

	void Publisher::registerEvents(const vector<string>& eventNames)
	{
	    publisherImpl_->registerEvents(eventNames);
	    return;
	}


	set<string> Publisher::listEvents() const
	{

		return publisherImpl_->listEvents();
	}

    set<string> Publisher::listEventObservers (const string& eventName) const
    {
    	return publisherImpl_->listEventObservers(eventName);
    }

    EventData::~EventData()
    {

    }
}


