// ----------------------------------------------------------------------------
// DisplayElement.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _STANDALONE_DISPLAY_ELEMENT_H_
#define _STANDALONE_DISPLAY_ELEMENT_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "NewhavenDisplay.h"


namespace Standalone
{

class DisplayElement
{
public:
  DisplayElement();
  static const uint8_t DISPLAY_WIDTH_MAX = 20;
  void setDisplayPosition(const uint8_t display_position);
  uint8_t getDisplayPosition();
  void setDisplayWidth(const uint8_t display_width);
  uint8_t getDisplayWidth();
  void setLeftJustify();
  void setRightJustify();
  virtual String getDisplayString() {};
  void updateOnDisplay(NewhavenDisplay &display, int frame);
  void addToFrame(int frame);
  void addToAllFrames();
  void removeFromFrame(int frame);
  bool inFrame(int frame);
  template<typename T>
  void setPaddingChar(const T value)
  {
    String string = String(value);
    if (string.length() > 0)
    {
      padding_char_ = string.charAt(0);
    }
    else
    {
      padding_char_ = ' ';
    }
  }
  void resetDefaultPaddingChar();
  char getPaddingChar();
protected:
  void setDisplayDirty();
private:
  typedef uint16_t frames_t;
  uint8_t display_position_;
  uint8_t display_width_;
  bool left_justify_;
  frames_t frames_;
  bool display_dirty_;
  char padding_char_;
  friend class Server;
};
}
#endif
