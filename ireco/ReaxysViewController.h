//
//  ReaxysViewController.h
//  ireco
//
//  Created by Karulin Boris on 03.10.11.
//  Copyright 2011 Scite. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ReaxysViewController : UIViewController <UINavigationControllerDelegate, UIWebViewDelegate>
{
   UIWebView *webView;
   UIActivityIndicatorView *activityView;
}
@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *activityView;

@property (nonatomic, retain) NSString *smiles;

@end
