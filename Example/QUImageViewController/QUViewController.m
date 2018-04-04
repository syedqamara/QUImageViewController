//
//  QUViewController.m
//  QUImageViewController
//
//  Created by etdev24 on 04/04/2018.
//  Copyright (c) 2018 etdev24. All rights reserved.
//

#import "QUViewController.h"
#import <QUImageViewController/QUImageViewController.h>
@interface QUViewController (){
    BOOL isImageDownloaded;
    NSURL *imageURL;
}
@property (weak, nonatomic) IBOutlet UIImageView *imageView;

@end

@implementation QUViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    imageURL = [NSURL URLWithString:@"https://wallpaperbrowse.com/media/images/303836.jpg"];
    [QUSimpleImageDownloader downloadImageForURL:imageURL canonicalURL:nil completion:^(UIImage *image) {
        dispatch_async(dispatch_get_main_queue(), ^{
            isImageDownloaded = YES;
            self.imageView.image = image;
        });
    }];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)didTapImageView:(id)sender {
    if (isImageDownloaded) {
        QUImageInfo *imageInfo = [[QUImageInfo alloc]init];
        imageInfo.imageURL = imageURL;
        QUImageViewController *imageVC = [[QUImageViewController alloc]initWithImageInfo:imageInfo mode:(QUImageViewControllerMode_Image) backgroundStyle:(QUImageViewControllerBackgroundOption_Blurred)];
        imageVC.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
        imageVC.modalPresentationStyle = UIModalPresentationOverCurrentContext;
        [self presentViewController:imageVC animated:YES completion:nil];
    }
}

@end
