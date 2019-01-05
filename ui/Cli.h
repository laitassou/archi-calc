#pragma once

#include <string>
#include <memory>
#include <iostream>


namespace myDesign
{

	class Cli //: public UserInterface
	{
		class cliImpl;

	public:
		Cli(std::istream & , std::ostream &);
		~Cli();

		void execute(bool supressStartupMessage = false,, echo bool=false);

	private:
		void postMessage(const std::string & m) override;





	};

}