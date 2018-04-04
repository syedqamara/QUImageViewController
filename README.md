QUImageViewController
======================

[![CI Status](http://img.shields.io/travis/etdev24/QUImageViewController.svg?style=flat)](https://travis-ci.org/etdev24/QUImageViewController)
[![Version](https://img.shields.io/cocoapods/v/QUImageViewController.svg?style=flat)](http://cocoapods.org/pods/QUImageViewController)
[![License](https://img.shields.io/cocoapods/l/QUImageViewController.svg?style=flat)](http://cocoapods.org/pods/QUImageViewController)
[![Platform](https://img.shields.io/cocoapods/p/QUImageViewController.svg?style=flat)](http://cocoapods.org/pods/QUImageViewController)

An interactive iOS image viewer that does it all: double tap to zoom, flick to dismiss, et cetera.



## Pull Requests

Pull requests are welcome, but should be submitted on the `dev` branch. Exceptions will be made for critical bug fixes.

## What Does it Do?

QUImageViewController is like a "light box" for iOS. It's similar to image viewers you may have seen in apps like Twitter, Tweetbot, and others. It presents an image in a full-screen interactive view. Users can pan and zoom, and use Tweetbot-style dynamic gestures to dismiss it with a fun flick.

## Screenshot

<img width="320" src="https://raw.githubusercontent.com/jaredsinclair/QUImageViewController/master/QU-image-viewer-screenshot.png" />

## How Does it Work?

Usage is pretty simple, though there are some cool options and delegate methods if you need them. Here's what your simplest implementation might look like:

```objc
- (void)someBigImageButtonTapped:(id)sender {
    
    // Create image info
    QUImageInfo *imageInfo = [[QUImageInfo alloc] init];
    imageInfo.image = YOUR_SOURCE_IMAGE;
    imageInfo.referenceRect = self.bigImageButton.frame;
    imageInfo.referenceView = self.bigImageButton.superview;
    
    // Setup view controller
    QUImageViewController *imageViewer = [[QUImageViewController alloc]
                                           initWithImageInfo:imageInfo
                                           mode:QUImageViewControllerMode_Image
                                           backgroundStyle:QUImageViewControllerBackgroundOption_Scaled];
    
    // Present the view controller.
    [imageViewer showFromViewController:self transition:QUImageViewControllerTransition_FromOriginalPosition];
}
```

That's it.

## Extras and Options

- **Image Downloads:** If you don't have the source image already, just use the `imageURL` property when setting up the `QUImageInfo` instance. QUImageViewController will handle downloading the image for you.

- **Background Styles:** Choose between a scaled-and-dimmed style or a scaled-dimmed-and-blurred background style. The latter is like the one used in Tweetbot.

- **Alt-Text Mode:** Need to show the alt text for an image? QUImageViewController includes an alternate mode that shows a full-screen, centered text view using the same style as the image mode.

- **Handle Long-Presses:** Implement an `interactionsDelegate` to respond to long presses on the image, or to temporarily disable user interactions (comes in handy if you show an overlay that could cause gesture conflict).

## License

MIT License, see the included file.
