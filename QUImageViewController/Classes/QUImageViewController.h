//
//  QUImageViewController.h
//
//
//  Created by Syed Qamar Abbas on 3/28/14.
//  Copyright (c) 2018 Eureka, TS. All rights reserved.
//

@import UIKit;

#import "QUImageInfo.h"
#import "QUAnimatedGIFUtility.h"
#import "QUSimpleImageDownloader.h"

///--------------------------------------------------------------------------------------------------------------------
/// Definitions
///--------------------------------------------------------------------------------------------------------------------

@protocol QUImageViewControllerDismissalDelegate;
@protocol QUImageViewControllerOptionsDelegate;
@protocol QUImageViewControllerInteractionsDelegate;
@protocol QUImageViewControllerAccessibilityDelegate;
@protocol QUImageViewControllerAnimationDelegate;

typedef NS_ENUM(NSInteger, QUImageViewControllerMode) {
    QUImageViewControllerMode_Image,
    QUImageViewControllerMode_AltText,
};

typedef NS_ENUM(NSInteger, QUImageViewControllerTransition) {
    QUImageViewControllerTransition_FromOriginalPosition,
    QUImageViewControllerTransition_FromOffscreen,
};

typedef NS_OPTIONS(NSInteger, QUImageViewControllerBackgroundOptions) {
    QUImageViewControllerBackgroundOption_None = 0,
    QUImageViewControllerBackgroundOption_Scaled = 1 << 0,
    QUImageViewControllerBackgroundOption_Blurred = 1 << 1,
};

extern CGFloat const QUImageViewController_DefaultAlphaForBackgroundDimmingOverlay;
extern CGFloat const QUImageViewController_DefaultBackgroundBlurRadius;

///--------------------------------------------------------------------------------------------------------------------
/// QUImageViewController
///--------------------------------------------------------------------------------------------------------------------

@interface QUImageViewController : UIViewController

@property (strong, nonatomic, readonly) QUImageInfo *imageInfo;

@property (strong, nonatomic, readonly) UIImage *image;

@property (assign, nonatomic, readonly) QUImageViewControllerMode mode;

@property (assign, nonatomic, readonly) QUImageViewControllerBackgroundOptions backgroundOptions;

@property (weak, nonatomic, readwrite) id <QUImageViewControllerDismissalDelegate> dismissalDelegate;

@property (weak, nonatomic, readwrite) id <QUImageViewControllerOptionsDelegate> optionsDelegate;

@property (weak, nonatomic, readwrite) id <QUImageViewControllerInteractionsDelegate> interactionsDelegate;

@property (weak, nonatomic, readwrite) id <QUImageViewControllerAccessibilityDelegate> accessibilityDelegate;

@property (weak, nonatomic, readwrite) id <QUImageViewControllerAnimationDelegate> animationDelegate;

/**
 Designated initializer.
 
 @param imageInfo The source info for image and transition metadata. Required.
 
 @param mode The mode to be used. (QUImageViewController has an alternate alt text mode). Required.
 
 @param backgroundStyle Currently, either scaled-and-dimmed, or scaled-dimmed-and-blurred. 
 The latter is like Tweetbot 3.0's background style.
 */
- (instancetype)initWithImageInfo:(QUImageInfo *)imageInfo
                             mode:(QUImageViewControllerMode)mode
                  backgroundStyle:(QUImageViewControllerBackgroundOptions)backgroundOptions;

/**
 QUImageViewController is presented from viewController as a UIKit modal view controller.
 
 It's first presented as a full-screen modal *without* animation. At this stage the view controller
 is merely displaying a snapshot of viewController's topmost parentViewController's view.
 
 Next, there is an animated transition to a full-screen image viewer.
 */
- (void)showFromViewController:(UIViewController *)viewController
                    transition:(QUImageViewControllerTransition)transition;

/**
 Dismisses the image viewer. Must not be called while previous presentation or dismissal is still in flight.
 */
- (void)dismiss:(BOOL)animated;

@end

///--------------------------------------------------------------------------------------------------------------------
/// Dismissal Delegate
///--------------------------------------------------------------------------------------------------------------------

@protocol QUImageViewControllerDismissalDelegate <NSObject>

/**
 Called after the image viewer has finished dismissing.
 */
- (void)imageViewerDidDismiss:(QUImageViewController *)imageViewer;

@end

///--------------------------------------------------------------------------------------------------------------------
/// Options Delegate
///--------------------------------------------------------------------------------------------------------------------

@protocol QUImageViewControllerOptionsDelegate <NSObject>
@optional

/**
 Return YES if you want the image thumbnail to fade to/from zero during presentation
 and dismissal animations.
 
 This may be helpful if the reference image in your presenting view controller has been
 dimmed, such as for a dark mode. QUImageViewController otherwise presents the animated 
 image view at full opacity, which can look jarring.
 */
- (BOOL)imageViewerShouldFadeThumbnailsDuringPresentationAndDismissal:(QUImageViewController *)imageViewer;

/**
 The font used in the alt text mode's text view.
 
 This method is only used with `QUImageViewControllerMode_AltText`.
 */
- (UIFont *)fontForAltTextInImageViewer:(QUImageViewController *)imageViewer;

/**
 The tint color applied to tappable text and selection controls.
 
 This method is only used with `QUImageViewControllerMode_AltText`.
 */
- (UIColor *)accentColorForAltTextInImageViewer:(QUImageViewController *)imageView;

/**
 The background color of the image view itself, not to be confused with the background
 color for the view controller's view. 
 
 You may wish to override this method if displaying an image with dark content on an 
 otherwise clear background color (such as images from the XKCD What If? site).
 
 The default color is `[UIColor clearColor]`.
 */
- (UIColor *)backgroundColorImageViewInImageViewer:(QUImageViewController *)imageViewer;

/**
 Defaults to `QUImageViewController_DefaultAlphaForBackgroundDimmingOverlay`.
 */
- (CGFloat)alphaForBackgroundDimmingOverlayInImageViewer:(QUImageViewController *)imageViewer;

/**
 Used with a QUImageViewControllerBackgroundStyle_ScaledDimmedBlurred background style.
 
 Defaults to `QUImageViewController_DefaultBackgroundBlurRadius`. The larger the radius,
 the more profound the blur effect. Larger radii may lead to decreased performance on
 older devices. To offset this, QUImageViewController applies the blur effect to a
 scaled-down snapshot of the background view.
 */
- (CGFloat)backgroundBlurRadiusForImageViewer:(QUImageViewController *)imageViewer;

@end

///--------------------------------------------------------------------------------------------------------------------
/// Interactions Delegate
///--------------------------------------------------------------------------------------------------------------------

@protocol QUImageViewControllerInteractionsDelegate <NSObject>
@optional

/**
 Called when the image viewer detects a long press.
 */
- (void)imageViewerDidLongPress:(QUImageViewController *)imageViewer atRect:(CGRect)rect;

/**
 Called when the image viewer is deciding whether to respond to user interactions.
 
 You may need to return NO if you are presenting custom, temporary UI on top of the image viewer. 
 This method is called more than once. Returning NO does not "lock" the image viewer.
 */
- (BOOL)imageViewerShouldTemporarilyIgnoreTouches:(QUImageViewController *)imageViewer;

/**
 Called when the image viewer is deciding whether to display the Menu Controller, to allow the user to copy the image to the general pasteboard.
 */
- (BOOL)imageViewerAllowCopyToPasteboard:(QUImageViewController *)imageViewer;

@end

///--------------------------------------------------------------------------------------------------------------------
/// Accessibility Delegate
///--------------------------------------------------------------------------------------------------------------------


@protocol QUImageViewControllerAccessibilityDelegate <NSObject>
@optional

- (NSString *)accessibilityLabelForImageViewer:(QUImageViewController *)imageViewer;

- (NSString *)accessibilityHintZoomedInForImageViewer:(QUImageViewController *)imageViewer;

- (NSString *)accessibilityHintZoomedOutForImageViewer:(QUImageViewController *)imageViewer;

@end

///---------------------------------------------------------------------------------------------------
/// Animation Delegate
///---------------------------------------------------------------------------------------------------

@protocol QUImageViewControllerAnimationDelegate <NSObject>
@optional

- (void)imageViewerWillBeginPresentation:(QUImageViewController *)imageViewer withContainerView:(UIView *)containerView;

- (void)imageViewerWillAnimatePresentation:(QUImageViewController *)imageViewer withContainerView:(UIView *)containerView duration:(CGFloat)duration;

- (void)imageViewer:(QUImageViewController *)imageViewer willAdjustInterfaceForZoomScale:(CGFloat)zoomScale withContainerView:(UIView *)containerView duration:(CGFloat)duration;

- (void)imageViewerWillBeginDismissal:(QUImageViewController *)imageViewer withContainerView:(UIView *)containerView;

- (void)imageViewerWillAnimateDismissal:(QUImageViewController *)imageViewer withContainerView:(UIView *)containerView duration:(CGFloat)duration;

@end








