#pragma once

#include <utility>

class Window
{
public:

	virtual bool Init() = 0;

	virtual unsigned int							GetWidth() = 0;
	virtual unsigned int							GetHeight() = 0;
	virtual std::pair<unsigned int, unsigned int>	GetWindowSize() = 0;
	virtual void*									GetNativeWindow() const = 0;
	virtual bool									IsWindowOpen() = 0;
	virtual void									Close() = 0;
	virtual void									Display() = 0;
	
	virtual void									SetWidth( unsigned int width ) = 0;
	virtual void									SetHeight( unsigned int Height ) = 0;
	virtual void									SetWindowSize( std::pair<unsigned int, unsigned int> size ) = 0;



};

