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

@interface KetcherViewController : UIViewController <UINavigationControllerDelegate, UIWebViewDelegate>
{
   UIWebView *webView;
   UIActivityIndicatorView *activityView;
@private
   NSString *molfile;
   UIImage *prevImage;
   Recognizer *recognizer;
   NSThread *recognizerThread;
   BOOL keepAlive;
   MagnifierView *loupe;
   NSTimer *touchTimer;
}    

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *activityView;

@property (nonatomic, retain) IBOutlet UIBarButtonItem *findInReaxysButton;

@property (nonatomic, retain) NSString *molfile;
@property (nonatomic, retain) UIImage *prevImage;
@property (nonatomic, retain) Recognizer *recognizer;
@property (nonatomic, retain) NSThread *recognizerThread;
@property (nonatomic, retain) NSTimer *touchTimer;

- (void)setupKetcher:(UIImage *)image;
- (void)loadMolfileToKetcher;
- (NSString *)saveSmilesFromKetcher;
- (void)recognizerThreadProc;
- (void)recognizingProc:(UIImage *)image;

@end
