#pragma once

const UID UIDComponent3 = 103;

struct  IComponent3 : IUnknown
{
	virtual int Calculate(int x) = 0;
};

const UID UIDComponent4 = 104;

struct  IComponent4 : IUnknown
{
	virtual int Calculate(int x) = 0;
};

