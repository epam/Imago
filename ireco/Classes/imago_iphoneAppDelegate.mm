//
//  imago_iphoneAppDelegate.m
//  imago-iphone
//
//  Created by Boris Karulin on 19.10.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "imago_iphoneAppDelegate.h"
#import "RootViewController.h"
#import "imago_c.h"
#import "FileJPG.h"
#import "FilePNG.h"
#import "ImageFilter.h"


@implementation imago_iphoneAppDelegate

@synthesize window;
@synthesize navigationController;


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.
    
    // Add the navigation controller's view to the window and display.
    //[window addSubview:navigationController.view];
    [window addSubview:imageView];
    [window makeKeyAndVisible];

   {
      gga::FileJPG jpg;
      gga::FilePNG png;
      gga::Image   img;
      
      NSString *path = [[NSBundle mainBundle] pathForResource:@"photo10" ofType:@"jpg"];
      
      NSLog(@"Let's start\n");
      
      if(jpg.load([path cStringUsingEncoding:NSASCIIStringEncoding], &img))
      {
         gga::ImageFilter flt(img);
         // compute optimal default parameters based on image resiolution
         flt.Parameters.StretchImage = true;
         flt.Parameters.UnsharpMaskRadius = std::min(120, int(std::min(img.getWidth(), img.getHeight())/2));
         flt.Parameters.UnsharpMaskAmount    = 9.;
         flt.Parameters.UnsharpMaskThreshold = 120;
         flt.Parameters.UnsharpMaskAmount2   = 0.;//3.;
         flt.Parameters.UnsharpMaskThreshold2= 150;
         flt.Parameters.CropBorder   = 16;//0;
         flt.Parameters.RadiusBlur1  = 4;
         flt.Parameters.RadiusBlur2  = 4;// 5 - 4 - 3
         flt.Parameters.SmallDirtSize= 1;//2;   // it's radius == size/2
         flt.Parameters.VignettingHoleDistance = std::min(48, (int)img.getWidth()/8);
         
         flt.prepareImageForVectorization();
         NSString *resPath = [[path stringByDeletingPathExtension] stringByAppendingString:@".png"];
         //png.save([resPath cStringUsingEncoding:NSASCIIStringEncoding], img);
         std::vector<size_t> whistogram;
         gga::Coord w = flt.computeLineWidthHistogram(&whistogram);
         NSLog(@"Line Width = %d\n", (int)w);
         
         /*
         UIImage *resImage = [UIImage imageWithContentsOfFile: resPath];
         imageView.image = resImage;
         [imageView sizeToFit];
         */
      }
   }
   
   
   /*
    NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"_png"];
    imagoLoadPngImageFromFile([path cStringUsingEncoding:NSASCIIStringEncoding]);
    imagoRecognize();
    char *buf;
    int bs;
    imagoSaveMolToBuffer(&buf, &bs);
    NSLog([NSString stringWithCString:buf encoding:NSASCIIStringEncoding]);
    NSLog(@"Done!");
   */
   
    

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}


- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
	[navigationController release];
	[window release];
	[super dealloc];
}


@end

