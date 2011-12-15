//
//  CropView.m
//  ireco
//
//  Created by Boris Karulin on 15.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "CropView.h"

const int THRESHOLD = 50;

@implementation CropView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect       myFrame = CGRectZero;
    CGRect       bounds = self.bounds;
    
    [[UIColor colorWithWhite:0.25 alpha:0.5] set];
    
    if (currentFrame.origin.x > 0)
    {
        myFrame = CGRectMake(0.0, 0.0, currentFrame.origin.x, CGRectGetHeight(bounds));
        UIRectFill(myFrame);
    }
    if (currentFrame.origin.y > 0)
    {
        myFrame = CGRectMake(currentFrame.origin.x, 0.0, currentFrame.size.width, CGRectGetMinY(currentFrame));
        UIRectFill(myFrame);
    }
    if (CGRectGetMaxX(currentFrame) < bounds.size.width)
    {
        myFrame = CGRectMake(CGRectGetMaxX(currentFrame), 0.0, CGRectGetWidth(bounds) - CGRectGetMaxX(currentFrame), CGRectGetHeight(bounds));
        UIRectFill(myFrame);
    }
    if (CGRectGetMaxY(currentFrame) < bounds.size.height)
    {
        myFrame = CGRectMake(currentFrame.origin.x, CGRectGetMaxY(currentFrame), currentFrame.size.width, CGRectGetHeight(bounds) - CGRectGetMaxY(currentFrame));
        UIRectFill(myFrame);
    }
    
    myFrame = currentFrame;
    
    // Set the line width to 4 and inset the rectangle by
    // 5 pixels on all sides to compensate for the wider line.
    CGContextSetLineWidth(context, 4);
    CGRectInset(myFrame, 2, 2);
    
    [[UIColor whiteColor] set];
    UIRectFrame(myFrame);    
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView:self];
    //CGRect frame = [self frame];

    cropMove = 0;
    
    if (ABS(pos.x - currentFrame.origin.x) < THRESHOLD)
        cropMove += MoveLeft;
    if (ABS(pos.y - currentFrame.origin.y) < THRESHOLD)
        cropMove += MoveTop;
    if (ABS(pos.x - CGRectGetMaxX(currentFrame)) < THRESHOLD)
        cropMove += MoveRight;
    if (ABS(pos.y - CGRectGetMaxY(currentFrame)) < THRESHOLD)
        cropMove += MoveBottom;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView:[self superview]];
    //CGRect frame = [self frame];
    
    pos.x = MAX(pos.x, initialFrame.origin.x);
    pos.y = MAX(pos.y, initialFrame.origin.y);
    pos.x = MIN(pos.x, CGRectGetMaxX(initialFrame));
    pos.y = MIN(pos.y, CGRectGetMaxY(initialFrame));
    
    if (cropMove & MoveLeft) 
    {
        pos.x = MIN(pos.x, CGRectGetMaxX(currentFrame) - 4 * THRESHOLD);
        currentFrame.size.width += currentFrame.origin.x - pos.x;
        currentFrame.origin.x = pos.x;
    } else if (cropMove & MoveRight)
    {
        pos.x = MAX(pos.x, currentFrame.origin.x + 4 * THRESHOLD);
        currentFrame.size.width = pos.x - currentFrame.origin.x;
    }
    
    if (cropMove & MoveTop)
    {
        pos.y = MIN(pos.y, CGRectGetMaxY(currentFrame) - 4 * THRESHOLD);
        currentFrame.size.height += currentFrame.origin.y - pos.y;
        currentFrame.origin.y = pos.y;
    } else if (cropMove & MoveBottom)
    {
        pos.y = MAX(pos.y, currentFrame.origin.y + 4 * THRESHOLD);
        currentFrame.size.height = pos.y - currentFrame.origin.y;
    }
    
    if (cropMove > 0) {
        [self setNeedsDisplay];
    }
    //self.frame = frame;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    cropMove = 0;
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    cropMove = 0;
}

- (void)setInitialFrame:(CGRect)frame
{
    initialFrame = frame;
    currentFrame = frame;
    [self setNeedsDisplay];
}

- (CGRect)cropRect
{
    return CGRectOffset(currentFrame, -initialFrame.origin.x, -initialFrame.origin.y);
}

@end
