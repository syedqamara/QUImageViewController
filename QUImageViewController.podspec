#
# Be sure to run `pod lib lint QUImageViewController.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'QUImageViewController'
  s.version          = '0.1.0'
  s.summary          = 'An interactive iOS image viewer that does it all: double tap to zoom, flick to dismiss, et cetera.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
QUImageViewController is like a "light box" for iOS. It's similar to image viewers you may have seen in apps like Twitter, Tweetbot, and others. It presents an image in a full-screen interactive view. Users can pan and zoom, and use Tweetbot-style dynamic gestures to dismiss it with a fun flick.
                       DESC

  s.homepage         = 'https://github.com/syedqamara/QUImageViewController'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'syedqamara' => 'syedqamar.a1@gmail.com' }
  s.source           = { :git => 'https://github.com/syedqamara/QUImageViewController.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '6.0'

  s.source_files = 'QUImageViewController/Classes/**/*'
  
  # s.resource_bundles = {
  #   'QUImageViewController' => ['QUImageViewController/Assets/*.png']
  # }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
