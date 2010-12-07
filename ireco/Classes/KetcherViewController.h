//
//  KetcherViewController.h
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface KetcherViewController : UIViewController <UINavigationControllerDelegate, UIWebViewDelegate>
{
   UIWebView *webView;
   UIActivityIndicatorView *activityView;
@private
   NSString *molfile;
   UIImage *prevImage;
}    

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *activityView;
@property (nonatomic, retain) NSString *molfile;
@property (nonatomic, retain) UIImage *prevImage;

- (void)setupKetcher:(UIImage *)image;
- (void)recognizingProc:(UIImage *)image;

@end
