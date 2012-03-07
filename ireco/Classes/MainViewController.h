#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioServices.h>

#import "CropView.h"
#import "OverlayViewController.h"
#import "KetcherViewController.h"
#import "MainWindow.h"

@interface MainViewController : UIViewController <UIImagePickerControllerDelegate, UIScrollViewDelegate,
                                                OverlayViewControllerDelegate, TapDetectingWindowDelegate>
{
    UIImageView *imageView;
    UIScrollView *scrollView;
    UIToolbar *toolbar;
    
    OverlayViewController *overlayViewController; // the camera custom overlay view
    KetcherViewController *ketcherViewController;

    UIImage *capturedImage;

@private
    UIBarButtonItem *recognizeButton;
}

@property (nonatomic, retain) IBOutlet CropView *cropView;
@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) IBOutlet UIScrollView *scrollView;
@property (nonatomic, retain) IBOutlet UIToolbar *toolbar;

@property (nonatomic, retain) OverlayViewController *overlayViewController;
@property (nonatomic, retain) KetcherViewController *ketcherViewController;

@property (nonatomic, retain) UIImage *capturedImage;

@property (nonatomic, retain) IBOutlet UIBarButtonItem *recognizeButton;

-(UIImage*)prepareImage:(UIImage*)anImage;
-(UIImage*)imageRotatedByRadians:(UIImage*)anImage:(CGFloat)radians;
-(void)updateScrollView;

// toolbar buttons
- (IBAction)photoLibraryAction:(id)sender;
- (IBAction)cameraAction:(id)sender;
- (IBAction)leftAction:(id)sender;
- (IBAction)rightAction:(id)sender;
- (IBAction)cropAction:(id)sender;
// navigation bar
- (IBAction)recognizeAction:(id)sender;

@end

