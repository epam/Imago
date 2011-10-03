#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioServices.h>

#import "OverlayViewController.h"
#import "KetcherViewController.h"
#import "ReaxysViewController.h"

@interface MainViewController : UIViewController <UIImagePickerControllerDelegate,
                                                OverlayViewControllerDelegate>
{
    UIImageView *imageView;
    UIToolbar *toolbar;
    
    OverlayViewController *overlayViewController; // the camera custom overlay view
    KetcherViewController *ketcherViewController;
    ReaxysViewController *reaxysViewController;

    UIImage *capturedImage;

@private
    UIBarButtonItem *recognizeButton;
    UIBarButtonItem *findInReaxysButton;
}

@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) IBOutlet UIToolbar *toolbar;

@property (nonatomic, retain) OverlayViewController *overlayViewController;
@property (nonatomic, retain) KetcherViewController *ketcherViewController;
@property (nonatomic, retain) ReaxysViewController *reaxysViewController;

@property (nonatomic, retain) UIImage *capturedImage;

@property (nonatomic, retain) IBOutlet UIBarButtonItem *recognizeButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *findInReaxysButton;

-(UIImage*)prepareImage:(UIImage*)anImage;
-(UIImage*)imageRotatedByRadians:(UIImage*)anImage:(CGFloat)radians;

// toolbar buttons
- (IBAction)photoLibraryAction:(id)sender;
- (IBAction)cameraAction:(id)sender;
- (IBAction)leftAction:(id)sender;
- (IBAction)rightAction:(id)sender;
// navigation bar
- (IBAction)recognizeAction:(id)sender;
- (IBAction)findInReaxysAction:(id)sender;

@end

