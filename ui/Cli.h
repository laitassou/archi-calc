#pragma once
#include "../utility/UserInterface.h"
#include <string>
#include <memory>
#include <iostream>


namespace mydesign
{

	class Cli : public UserInterface
	{
		class CliImpl;

		static const std::string PDCALC_VERSION ;

	public:
		Cli(std::istream & , std::ostream &);
		~Cli();

		void execute(bool supressStartupMessage = false,  bool echo=false);

	private:
		void postMessage(const std::string & m) override;

		void stackChanged () override;

		Cli(const Cli&) = delete;
		Cli(Cli&&) = delete;
    Cli& operator=(const Cli&) = delete;
    Cli& operator=(Cli&&) = delete;

		std::unique_ptr<CliImpl> pimpl_;

	};

}
