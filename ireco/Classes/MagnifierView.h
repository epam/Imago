#import <UIKit/UIKit.h>

@interface MagnifierView : UIView {
	UIView *viewToMagnify;
	CGPoint touchPoint;
}

@property (nonatomic, retain) UIView *viewToMagnify;
@property (assign) CGPoint touchPoint;

@end
