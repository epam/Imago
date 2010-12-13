#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioServices.h>

#import "OverlayViewController.h"
#import "KetcherViewController.h"

@interface MainViewController : UIViewController <UIImagePickerControllerDelegate,
                                                OverlayViewControllerDelegate>
{
    UIImageView *imageView;
    UIToolbar *toolbar;
    
    OverlayViewController *overlayViewController; // the camera custom overlay view
    KetcherViewController *ketcherViewController;

    UIImage *capturedImage;

@private
    UIBarButtonItem *recognizeButton;
}

@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) IBOutlet UIToolbar *toolbar;

@property (nonatomic, retain) OverlayViewController *overlayViewController;
@property (nonatomic, retain) KetcherViewController *ketcherViewController;

@property (nonatomic, retain) UIImage *capturedImage;

@property (nonatomic, retain) IBOutlet UIBarButtonItem *recognizeButton;

// toolbar buttons
- (IBAction)photoLibraryAction:(id)sender;
- (IBAction)cameraAction:(id)sender;
// navigation bar
- (IBAction)recognizeAction:(id)sender;

@end

