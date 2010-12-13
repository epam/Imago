#import "MainViewController.h"

@implementation MainViewController

@synthesize imageView, toolbar, overlayViewController, ketcherViewController, capturedImage, recognizeButton;


#pragma mark -
#pragma mark View Controller

- (void)viewDidLoad
{
    self.overlayViewController =
        [[[OverlayViewController alloc] initWithNibName:@"OverlayViewController" bundle:nil] autorelease];

    // as a delegate we will be notified when pictures are taken and when to dismiss the image picker
    self.overlayViewController.delegate = self;

    self.ketcherViewController =
        [[[KetcherViewController alloc] initWithNibName:@"KetcherViewController" bundle:nil] autorelease];

    self.capturedImage = nil;

    if (![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        // camera is not on this device, don't show the camera button
        NSMutableArray *toolbarItems = [NSMutableArray arrayWithCapacity:self.toolbar.items.count];
        [toolbarItems addObjectsFromArray:self.toolbar.items];
        [toolbarItems removeObjectAtIndex:2];
        [self.toolbar setItems:toolbarItems animated:NO];
    }
}

- (void)viewDidUnload
{
    self.imageView = nil;
    self.toolbar = nil;
    
    self.overlayViewController = nil;
    self.capturedImage = nil;
}

- (void)dealloc
{	
   [imageView release];
   [toolbar release];
    
   [overlayViewController release];
   [ketcherViewController release];
   if (capturedImage != nil)
      [capturedImage release];
    
   [super dealloc];
}


#pragma mark -
#pragma mark Toolbar Actions

- (void)showImagePicker:(UIImagePickerControllerSourceType)sourceType
{
    if (self.imageView.isAnimating)
        self.imageView.stopAnimating;
	
    if (self.capturedImage != nil)
    {
        [self.capturedImage release];
        self.capturedImage = nil;
    }
    
    if ([UIImagePickerController isSourceTypeAvailable:sourceType])
    {
        [self.overlayViewController setupImagePicker:sourceType];
        [self presentModalViewController:self.overlayViewController.imagePickerController animated:YES];
    }
}

- (IBAction)photoLibraryAction:(id)sender
{   
   [self showImagePicker:UIImagePickerControllerSourceTypePhotoLibrary];
}

- (IBAction)cameraAction:(id)sender
{
   [self showImagePicker:UIImagePickerControllerSourceTypeCamera];
}

#pragma mark -
#pragma mark Navigation Bar Actions

- (void)recognizeAction:(id)sender
{
   [self.navigationController pushViewController:ketcherViewController animated:YES]; 
   
   [self.ketcherViewController setupKetcher: self.capturedImage];
}
   
#pragma mark -
#pragma mark OverlayViewControllerDelegate

// as a delegate we are being told a picture was taken
- (void)didTakePicture:(UIImage *)picture
{
    if (self.capturedImage != nil)
       [self.capturedImage release];
    else
       self.recognizeButton.enabled = YES;

    self.capturedImage = picture;
   [self.capturedImage retain];
}

// as a delegate we are told to finished with the camera
- (void)didFinishWithCamera
{
    [self dismissModalViewControllerAnimated:YES];
    
    if (self.capturedImage != nil)
    {
        [self.imageView setImage:self.capturedImage];
    }
}

@end