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
	void setTextEditSize(int x=192,int y=42);//����������С
	bool setTextEditPasswordEnabled(bool isPassword);//�������������ģʽ
	void setTextEditPlaceHolder(const char* placeholder);//���������ռλ��
	std::string getTextEditString();//��ȡ���������
	TextEditWithCursor();
	~TextEditWithCursor();
	void onEnter();
private:
	void textEditEvent(Ref *pSender, TextField::EventType type);
	Sprite* cursorSprite;
	void addCursorSprite();//��ӹ��
	int getContentWidth();//��ȡ���λ��
	CC_SYNTHESIZE_RETAIN(Sprite*, tec_Sprite, TextEditSprite);//����򱳾�
	CC_SYNTHESIZE_RETAIN(TextField*, tec_TextField, TextFieldWithCursor);
};
#endif
