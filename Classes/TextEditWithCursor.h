#ifndef __TextEditWithCursor__  
#define __TextEditWithCursor__  
#include"cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;
class TextEditWithCursor:public LayerColor
{ 
public:
	virtual bool init();
	CREATE_FUNC(TextEditWithCursor);
	void setTextEditSize(int x=192,int y=42);//设置输入框大小
	bool setTextEditPasswordEnabled(bool isPassword);//设置输入框密码模式
	void setTextEditPlaceHolder(const char* placeholder);//设置输入框占位符
	std::string getTextEditString();//获取输入框内容
	TextEditWithCursor();
	~TextEditWithCursor();
	void onEnter();
private:
	void textEditEvent(Ref *pSender, TextField::EventType type);
	Sprite* cursorSprite;
	void addCursorSprite();//添加光标
	int getContentWidth();//获取光标位置
	CC_SYNTHESIZE_RETAIN(Sprite*, tec_Sprite, TextEditSprite);//输入框背景
	CC_SYNTHESIZE_RETAIN(TextField*, tec_TextField, TextFieldWithCursor);
};
#endif
