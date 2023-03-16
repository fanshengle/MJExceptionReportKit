#
# Be sure to run `pod lib lint MJExceptionReportKit.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'MJExceptionReportKit'
  s.version          = '0.1.0'
  s.summary          = 'A short description of MJExceptionReportKit.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/fanshengle/MJExceptionReportKit'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'fanshengle' => '1316838962@qq.com' }
  s.source           = { :git => 'https://github.com/fanshengle/MJExceptionReportKit.git', :tag => s.version.to_s }

  s.source_files = 'MJExceptionReportKit/Classes/**/*'
  
  s.ios.deployment_target = '11.0' 
#  s.static_framework = true
#  s.vendored_framework = 'MJExceptionReportKit/Products/MJExceptionReport.framework'
  
  s.subspec 'Core' do |ss|
    # 源文件
    ss.source_files = 'MJExceptionReportKit/Classes/Core/**/*'
    # 添加资源文件
    #ss.resourc = 'MJExceptionReportKit/Classes/Core/**/*'
    # 添加依赖第三方的framework
#    ss.vendored_framework = 'MJExceptionReportKit/Products/MJExceptionReport.framework'
  end
  
  s.subspec 'BaiduMapKit' do |ss|
      #源文件
#      ss.source_files = 'MJExceptionReportKit/BaiduMapKit/*.framework/Headers/*.h'
      #公开的头文件
#      ss.public_header_files = 'LPThirdPlatformKit/BaiduMapKit/*.framework/Headers/*.h'
      #依赖的系统库
      ss.frameworks =  'CoreLocation', 'QuartzCore', 'OpenGLES', 'SystemConfiguration', 'CoreGraphics', 'Security', 'CoreTelephony'
      #依赖的系统静态库
      ss.libraries =  'sqlite3.0', 'c++', 'z'
      #依赖的第三方库
      ss.vendored_frameworks = 'MJExceptionReportKit/BaiduMapKit/*.framework'
      #依赖的第三方静态库
      ss.vendored_libraries = 'MJExceptionReportKit/BaiduMapKit/thirdlibs/*.a'
      #预加载的第三方库路径
#      ss.preserve_paths = 'LPThirdPlatformKit/BaiduMapKit/**/*.{framework,a}'
      # Build Settings 修改设置中的 Runpath Search Paths
      ss.pod_target_xcconfig = { 'LD_RUNPATH_SEARCH_PATHS' => '$(PODS_ROOT)/MJExceptionReportKit/BaiduMapKit/' }
  end
  
  s.subspec 'Products' do |ss|
    ss.vendored_framework = 'MJExceptionReportKit/Products/MJExceptionReport.framework'
  end
end
