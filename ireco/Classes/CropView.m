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
    CGRect       myFrame = self.bounds;
    
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
    CGRect frame = [self frame];

    cropMove = 0;
    
    if (pos.x < THRESHOLD)
        cropMove += MoveLeft;
    if (pos.y < THRESHOLD)
        cropMove += MoveTop;
    if (pos.x > frame.size.width - THRESHOLD)
        cropMove += MoveRight;
    if (pos.y > frame.size.height - THRESHOLD)
        cropMove += MoveBottom;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView:[self superview]];
    CGRect frame = [self frame];
    
    pos.x = MAX(pos.x, initialFrame.origin.x);
    pos.y = MAX(pos.y, initialFrame.origin.y);
    pos.x = MIN(pos.x, initialFrame.origin.x+initialFrame.size.width);
    pos.y = MIN(pos.y, initialFrame.origin.y+initialFrame.size.height);
    
    if (cropMove & MoveLeft) 
    {
        pos.x = MIN(pos.x, frame.origin.x + frame.size.width - 4 * THRESHOLD);
        frame.size.width += frame.origin.x - pos.x;
        frame.origin.x = pos.x;
    } else if (cropMove & MoveRight)
    {
        pos.x = MAX(pos.x, frame.origin.x + 4 * THRESHOLD);
        frame.size.width = pos.x - frame.origin.x;
    }
    
    if (cropMove & MoveTop)
    {
        pos.y = MIN(pos.y, frame.origin.y + frame.size.height - 4 * THRESHOLD);
        frame.size.height += frame.origin.y - pos.y;
        frame.origin.y = pos.y;
    } else if (cropMove & MoveBottom)
    {
        pos.y = MAX(pos.y, frame.origin.y + 4 * THRESHOLD);
        frame.size.height = pos.y - frame.origin.y;
    }
    
    
    self.frame = frame;
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
    self.frame = frame;
}

@end
