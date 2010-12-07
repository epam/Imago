//
//  KetcherViewController.h
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioServices.h>

@interface KetcherViewController : UIViewController <UINavigationControllerDelegate>
{
   UIWebView *webView;
   
@private
}    

@property (nonatomic, retain) IBOutlet UIWebView *webView;

- (void)setupKetcher:(NSString *)molfile;

@end
