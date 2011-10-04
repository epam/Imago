#import "MagnifierView.h"
#import <QuartzCore/QuartzCore.h>

@implementation MagnifierView
@synthesize viewToMagnify;

- (id)initWithFrame:(CGRect)frame {
	if (self = [super initWithFrame:CGRectMake(0, 0, 80, 80)]) {
		// make the circle-shape outline with a nice border.
		self.layer.borderColor = [[UIColor lightGrayColor] CGColor];
		self.layer.borderWidth = 3;
		self.layer.cornerRadius = 40;
		self.layer.masksToBounds = YES;
	}
	return self;
}

/*
- (id)initWithFrame:(CGRect)frame {
    return [self initWithFrame:frame radius:100];
}
 
- (id)initWithFrame:(CGRect)frame radius:(int)r 
{
    if ((self = [super initWithFrame:CGRectMake(0, 0, r, r)]))
    {
        //Make the layer circular.
        self.layer.cornerRadius = r / 2;
        self.layer.masksToBounds = YES;
        
        UIImage* image = [UIImage imageNamed:@"Loupe.png"];
        
        imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, radius, radius)];
        imageView.image = image;
        [self addSubview:imageView];
    }
    
    return self;
}
*/

- (CGPoint)touchPoint
{
    return touchPoint;
}

- (void)setTouchPoint:(CGPoint)pt {
    // pt is in the coordinate space of the magnified view, which may be 
    // different than the coordinate system of the magnifier's superview. 
    // Transform it to superview coordinates.
    //touchPoint = [viewToMagnify convertPoint:pt toView:self.superview];
	touchPoint = pt;
    
	// whenever touchPoint is set, 
	// update the position of the magnifier (to just above what's being magnified)
	self.center = CGPointMake(pt.x, pt.y-60);
}

- (void)drawRect:(CGRect)rect {
	// here we're just doing some transforms on the view we're magnifying,
	// and rendering that view directly into this view,
	// rather than the previous method of copying an image.
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGContextTranslateCTM(context,1*(self.frame.size.width*0.5),1*(self.frame.size.height*0.5));
	CGContextScaleCTM(context, 1.5, 1.5);

    // touchPoint is in OUR coordinate space. Transform to the magnified view's
    // space to magnify.
    //CGPoint magnifiedPoint = [viewToMagnify convertPoint:touchPoint fromView:self.superview];
    //CGContextTranslateCTM(context, -magnifiedPoint.x, -magnifiedPoint.y);
	CGContextTranslateCTM(context,-1*(touchPoint.x),-1*(touchPoint.y));
	[self.viewToMagnify.layer renderInContext:context];
}

- (void)dealloc {
	[viewToMagnify release];
	[super dealloc];
}


@end
