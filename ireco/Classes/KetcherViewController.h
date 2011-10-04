//
//  KetcherViewController.h
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "chemical_structure_recognizer.h"
#import "Recognizer.h"
#import "MagnifierView.h"
#import "ReaxysViewController.h"

@interface KetcherViewController : UIViewController <UINavigationControllerDelegate, UIWebViewDelegate>
{
   ReaxysViewController *reaxysViewController;
    
   UIWebView *webView;
   UIActivityIndicatorView *activityView;
   UINavigationItem *navigationItem;
@private
   NSString *molfile;
   UIImage *prevImage;
   Recognizer *recognizer;
   NSThread *recognizerThread;
   BOOL keepAlive;
   MagnifierView *loupe;
   NSTimer *touchTimer;
}    

@property (nonatomic, retain) ReaxysViewController *reaxysViewController;

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *activityView;
@property (nonatomic, retain) IBOutlet UINavigationItem *navigationItem;

@property (nonatomic, retain) NSString *molfile;
@property (nonatomic, retain) UIImage *prevImage;
@property (nonatomic, retain) Recognizer *recognizer;
@property (nonatomic, retain) NSThread *recognizerThread;
@property (nonatomic, retain) NSTimer *touchTimer;

- (IBAction)findInReaxys:(id)sender;
- (void)setupKetcher:(UIImage *)image;
- (void)loadMolfileToKetcher;
- (NSString *)saveSmilesFromKetcher;
- (void)recognizerThreadProc;
- (void)recognizingProc:(UIImage *)image;

@end
