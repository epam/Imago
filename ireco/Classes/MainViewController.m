#import "MainViewController.h"

@implementation MainViewController

@synthesize imageView, toolbar, overlayViewController, ketcherViewController, capturedImages, recognizeButton;


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

    self.capturedImages = [NSMutableArray array];

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
    self.capturedImages = nil;
}

- (void)dealloc
{	
   [imageView release];
   [toolbar release];
    
   [overlayViewController release];
   [capturedImages release];
    
   [super dealloc];
}


#pragma mark -
#pragma mark Toolbar Actions

- (void)showImagePicker:(UIImagePickerControllerSourceType)sourceType
{
    if (self.imageView.isAnimating)
        self.imageView.stopAnimating;
	
    if (self.capturedImages.count > 0)
        [self.capturedImages removeAllObjects];
    
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
   
   [self.ketcherViewController setupKetcher: [self.capturedImages objectAtIndex:0]];
}
   
#pragma mark -
#pragma mark OverlayViewControllerDelegate

// as a delegate we are being told a picture was taken
- (void)didTakePicture:(UIImage *)picture
{
    if (self.capturedImages.count > 0)
       [self.capturedImages removeAllObjects];
    else
       self.recognizeButton.enabled = YES;

    [self.capturedImages addObject:picture];
}

// as a delegate we are told to finished with the camera
- (void)didFinishWithCamera
{
    [self dismissModalViewControllerAnimated:YES];
    
    if ([self.capturedImages count] > 0)
    {
        //if ([self.capturedImages count] == 1)
        {
            // we took a single shot
            [self.imageView setImage:[self.capturedImages objectAtIndex:0]];
        }/*
        else
        {
            // we took multiple shots, use the list of images for animation
            self.imageView.animationImages = self.capturedImages;
            
            if (self.capturedImages.count > 0)
                // we are done with the image list until next time
                [self.capturedImages removeAllObjects];  
            
            self.imageView.animationDuration = 5.0;    // show each captured photo for 5 seconds
            self.imageView.animationRepeatCount = 0;   // animate forever (show all photos)
            self.imageView.startAnimating;
        }*/
    }
}

@end