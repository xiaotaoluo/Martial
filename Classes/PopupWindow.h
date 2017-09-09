#ifndef __PopupWindow__  
#define __PopupWindow__  
#include "ui/CocosGUI.h"
#include "cocos2d.h"  
USING_NS_CC;
using namespace cocos2d::ui;
class PopupWindow : public  Layer
{
public:
	//获取唯一实例的公共方法
	static PopupWindow* getInstance();
	//设置弹窗背景
	void setWindowBackGround(const char* backgroundImage);
	//设置标题
	void setWindowTitle(const char* title, const char* fontname="",int fontsize=22);
	//通过系统字体设置内容文本
	void setContentText(const char* content, const char* fontname = "", int fontsize = 18, int padding = 35, int paddingTop = 25);
	//通过ttf文件设置内容文本
	void setContentTextWithTTF(const char* content, const char* fontname, int fontsize = 16, int padding = 40, int paddingTop = 25);
	//回调方法
	void setCallbackFunc(Object* target, SEL_CallFuncN callfun);
	//增加菜单按钮
	bool addMenuButton(const char* normalImage, const char* selectedImage , const char* title, const char* buttonTextFontName = "", int tag = 0);
	//增加Button
	bool addButton(const char* buttonImage, const char* titleText, const char* titleFontName="隶书", int titleFontSize = 25);
	//设置弹窗尺寸
	void setWindowSize(int x,int y);
	virtual void onEnter();
	virtual void onExit();

private:
	PopupWindow();
	~PopupWindow();
	static PopupWindow* pwInstence;
	//按钮响应
	void buttonCallback(Object* pSender);
	//内容文本边距
	int m_contentPadding;
	int m_contentPaddingTop;
	//监听器
	Object* m_callbackListener;
	SEL_CallFuncN m_callback;
	//Button响应事件
	void ButtonEvent(Ref*, cocos2d::ui::TouchEventType type);
	//Button数量
	int numBtn;
	//Button容器
	Vector<Button*> vecBtn;
	//添加变量及其get、set方法
	CC_SYNTHESIZE_RETAIN(Menu*, pw_Menu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, pw_BackGround, PopupWindowBackGround);
	CC_SYNTHESIZE_RETAIN(Text*, pw_Title, PopupWindowTitle);
	CC_SYNTHESIZE_RETAIN(Label*, pw_ContentText, PopupWindowContentText);
	CC_SYNTHESIZE_RETAIN(Button*, pw_Button, PopupWindowButton);

};
#endif
