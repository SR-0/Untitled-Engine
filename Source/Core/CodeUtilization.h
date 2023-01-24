#pragma once

/*
	"CodeUtilization" pattern (no clue, just because)

	"CodeUtilization" is experimental - if it
	doesnt work or becomes too much of a problem
	with either the devs or users, a decision
	will have to made between dynamic functionality
	and virtual override functionality, with
	virtual override functionality being the
	preferable choice depending on final design

	"CodeUtilization" is meant to give certain
	classes more dynamically diverse automated
	initialize/create, update, and terminate/
	destroy coding style/utilization by giving
	the user/dev a choice between dynamically
	settings previously mentioned functionality
	via lambdas and std::functions - and virtually
	overriding previously mentioned functionality
	within derived chosen classes - or with both
	via combination and priority code utilization
	values
*/

enum class CodeUtilization 
{
	DynamicFunction,
	VirtualOverride,
	Combination
};