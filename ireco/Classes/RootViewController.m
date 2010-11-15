//
//  RootViewController.m
//  imago-iphone
//
//  Created by Boris Karulin on 19.10.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "RootViewController.h"


@implementation RootViewController

#pragma mark -
#pragma mark View lifecycle

@synthesize imageView, myToolbar, overlayViewController, capturedImages;


#pragma mark -
#pragma mark View Controller

- (void)viewDidLoad
{
   self.overlayViewController =
   [[[OverlayViewController alloc] initWithNibName:@"OverlayViewController" bundle:nil] autorelease];
   
   // as a delegate we will be notified when pictures are taken and when to dismiss the image picker
   self.overlayViewController.delegate = self;
   
   self.capturedImages = [NSMutableArray array];
   
   if (![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
   {
      // camera is not on this device, don't show the camera button
      NSMutableArray *toolbarItems = [NSMutableArray arrayWithCapacity:self.myToolbar.items.count];
      [toolbarItems addObjectsFromArray:self.myToolbar.items];
      [toolbarItems removeObjectAtIndex:2];
      [self.myToolbar setItems:toolbarItems animated:NO];
   }
}

- (void)viewDidUnload
{
   self.imageView = nil;
   self.myToolbar = nil;
   
   self.overlayViewController = nil;
   self.capturedImages = nil;
}

- (void)dealloc
{	
	[imageView release];
	[myToolbar release];
   
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
#pragma mark OverlayViewControllerDelegate

// as a delegate we are being told a picture was taken
- (void)didTakePicture:(UIImage *)picture
{
   [self.capturedImages addObject:picture];
}

// as a delegate we are told to finished with the camera
- (void)didFinishWithCamera
{
   [self dismissModalViewControllerAnimated:YES];
   
   if ([self.capturedImages count] > 0)
   {
      if ([self.capturedImages count] == 1)
      {
         // we took a single shot
         [self.imageView setImage:[self.capturedImages objectAtIndex:0]];
      }
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
      }
   }
}

/*
- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}
*/

/*
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}
*/
/*
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}
*/
/*
- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
}
*/
/*
- (void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
}
*/

/*
 // Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	// Return YES for supported orientations.
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
 */

/*
#pragma mark -
#pragma mark Table view data source

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 0;
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
	// Configure the cell.

    return cell;
}


/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/


/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source.
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
    }   
}
*/


/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/


/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
	/*
	 <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
	 [self.navigationController pushViewController:detailViewController animated:YES];
	 [detailViewController release];
	 */
//}


#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc that aren't in use.
}

@end

