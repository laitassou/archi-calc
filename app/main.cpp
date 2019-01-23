#include <iostream>
#include <memory>
#include "ui/Cli.h"
#include "backend/CommandDispatcher.h"
#include "backend/AppObservers.h"
#include "backend/Stack.h"
//#include "backend/CoreCommands.h"

// I usually don't make blanket using namespace statements, but this
// example is meant to be simple.
using namespace mydesign;

using std::cout;
using std::endl;
using std::make_unique;


/*
void showmessage(){
	cout << "test" <<endl;
}
int  poewers(int x){
	return x*x*x;
}

*/
int main(int arc, char ** arv)
{
		Cli cli{std::cin, std::cout};

		CommandDispatcher ce{cli};
	  cli.attach(UserInterface::CommandEntered, make_unique<CommandIssuedObserver>(ce) );

	  Stack::Instance().attach(Stack::StackChanged, make_unique<StackUpdatedObserver>(cli) );
 		cli.execute();
/*
 showmessage();

 int y = poewers(5);
*/

	return 0;

}
