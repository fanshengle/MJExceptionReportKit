/*
 *  BMKOverlayView.h
 *  BMapKit
 *
 *  Copyright 2011 Baidu Inc. All rights reserved.
 *
 */
#import <UIKit/UIKit.h>
#import "BMKOverlay.h"
#import "BMKLineDrawType.h"

NS_ASSUME_NONNULL_BEGIN
/// 该类是地图覆盖物View的基类，提供绘制overlay的接口但本身并无实现，所有地图覆盖物View需要继承自此类
@interface BMKOverlayView : UIView
{
@package
    
    id <BMKOverlay> _overlay;
    BMKMapRect _boundingMapRect;
    CGAffineTransform _mapTransform;
    id _geometryDelegate;
    id _canDrawCache;
    BOOL keepScale;
    CFTimeInterval _lastTile;
    CFRunLoopTimerRef _scheduledScaleTimer;
    
    struct {
        unsigned int keepAlive:1;
        unsigned int levelCrossFade:1;
        unsigned int drawingDisabled:1;
        unsigned int usesTiledLayer:1;
    } _flags;
}

/// 初始化并返回一个overlay view
/// @param overlay 关联的overlay对象
/// @return 初始化成功则返回overlay view,否则返回nil
- (nullable instancetype)initWithOverlay:(id <BMKOverlay>)overlay;

/// 关联的overlay对象
@property (nonatomic, readonly) id <BMKOverlay> overlay;

/// 关联的纹理对象ID
@property (nonatomic, readonly) GLuint strokeTextureID;

/// 加载纹理图片
/// @param textureImage 图片对象，opengl要求图片宽高必须是2的n次幂，如果图片对象为nil，则清空原有纹理
/// @return openGL纹理ID, 若纹理加载失败返回0
- (GLuint)loadStrokeTextureImage:(UIImage *)textureImage __deprecated_msg("已废弃since 6.5.0，请使用BMKOverlayGLBasicView中textureImage字段");

/// 加载分段纹理绘制 所需的纹理图片
/// @param textureImages 必须UIImage数组，opengl要求图片宽高必须是2的n次幂，否则，返回NO，无法分段纹理绘制
/// @return 是否成功
- (BOOL)loadStrokeTextureImages:(NSArray<UIImage *> *)textureImages __deprecated_msg("已废弃since 6.5.0，请使用BMKMultiTexturePolylineView中textureImages字段");

/// 设置该overlay的GeometryDelegate
- (void)setOverlayGeometryDelegate:(id)delegate;

/**
 *将直角坐标转为overlay view坐标
 *@param mapPoint 直角坐标
 *@return 对应的view坐标
 */
- (CGPoint)pointForMapPoint:(BMKMapPoint)mapPoint;

/**
 *将overlay view坐标转为直角坐标
 *@param point view坐标
 *@return 对应的直角坐标
 */
- (BMKMapPoint)mapPointForPoint:(CGPoint)point;

/**
 *将二维地图投影矩形转为overlay view矩形
 *@param mapRect 二维地图投影矩形
 *@return 对应的view矩形
 */
- (CGRect)rectForMapRect:(BMKMapRect)mapRect;

/**
 *将overlay view区域转为二维地图投影区域
 *@param rect 指定的view矩形
 *@return 对应的二维地图投影矩形
 */
- (BMKMapRect)mapRectForRect:(CGRect)rect;

/**
 *判断ovlerlay view是否准备绘制内容
 *默认返回YES，如果用户设为NO，当需要绘制内容时要显示调用setNeedsDisplayInMapRect:zoomScale:方法
 *@param mapRect 需要更新的地图矩形区域
 *@param zoomScale 当前的缩放因子
 *@return 如果view准备好绘制内容，返回YES,否则返回NO
 */
- (BOOL)canDrawMapRect:(BMKMapRect)mapRect zoomScale:(BMKZoomScale)zoomScale;

/**
 *绘制overlay view内容
 *该方法默认不做任何事，子类需要重载该方法来绘制view的内容
 *@param mapRect 需要更新的地图矩形区域
 *@param zoomScale 当前的缩放因子
 *@param context 使用的graphics context
 */
- (void)drawMapRect:(BMKMapRect)mapRect zoomScale:(BMKZoomScale)zoomScale inContext:(CGContextRef)context;

/**
 *使view在给定矩形的区域无效,系统将重绘该区域
 *@param mapRect 需要更新的区域
 */
- (void)setNeedsDisplayInMapRect:(BMKMapRect)mapRect;     

#pragma mark - since 6.0 render函数无效
/**
 *使用OpenGLES 指定颜色绘制线
 @param points 直角坐标点
 @param pointCount 点个数
 @param strokeColor 线颜色
 @param lineWidth OpenGLES支持线宽尺寸
 @param looped 是否闭合, 如polyline会设置NO, polygon会设置YES.
 */

- (void)renderLinesWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount strokeColor:(UIColor *)strokeColor lineWidth:(CGFloat)lineWidth looped:(BOOL)looped __deprecated_msg("已废弃since 6.0.0，内部无实现");
/**
 *使用OpenGLES 按指定纹理绘制线
 @param points 直角坐标点
 @param pointCount 点个数
 @param lineWidth OpenGLES支持线宽尺寸
 @param textureID 纹理ID,使用- (void)loadStrokeTextureImage:(UIImage *)textureImage;加载
 @param looped 是否闭合, 如polyline会设置NO, polygon会设置YES.
 */
- (void)renderTexturedLinesWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount lineWidth:(CGFloat)lineWidth textureID:(GLuint)textureID looped:(BOOL)looped  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 *使用OpenGLES 指定颜色绘制线 since 5.0.0
 @param points 直角坐标点
 @param pointCount 点个数
 @param strokeColor 线颜色
 @param lineWidth OpenGLES支持线宽尺寸
 @param looped 是否闭合, 如polyline会设置NO, polygon会设置YES.
 @param lineDashType 虚线样式
 */
- (void)renderLinesWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount strokeColor:(UIColor *)strokeColor lineWidth:(CGFloat)lineWidth looped:(BOOL)looped lineDashType:(BMKLineDashType)lineDashType  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 *使用OpenGLES 绘制线
 @param points 直角坐标点
 @param pointCount 点个数
 @param strokeColor 线颜色
 @param lineWidth OpenGLES支持线宽尺寸
 @param looped 是否闭合, 如polyline会设置NO, polygon会设置YES.
 @param lineDash 是否虚线样式
 */
- (void)renderLinesWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount strokeColor:(UIColor *)strokeColor lineWidth:(CGFloat)lineWidth looped:(BOOL)looped lineDash:(BOOL)lineDash __deprecated_msg("已废弃since 5.0.0，内部无实现，请使用renderLinesWithPoints: pointCount: strokeColor: lineWidth:looped: lineDashType:");

/**
 *使用OpenGLES 分段纹理绘制线
 @param partPt 分段直角坐标点
 @param lineWidth OpenGLES支持线宽尺寸
 @param textureIndexs 分段纹理索引,使用- (void)loadStrokeTextureImage:(UIImage *)textureImage;加载
 @param isFoucs 是否使用分段纹理绘制
 */
-(void)renderTexturedLinesWithPartPoints:(NSArray*)partPt lineWidth:(CGFloat)lineWidth textureIndexs:(NSArray*)textureIndexs isFocus:(BOOL) isFoucs __deprecated_msg("已废弃since 5.0.0，内部无实现");

/**
 *使用OpenGLES 分段纹理绘制线
 @param partPt 分段直角坐标点
 @param lineWidth OpenGLES支持线宽尺寸
 @param textureIndexs 分段纹理索引,使用- (void)loadStrokeTextureImage:(UIImage *)textureImage;加载
 @param isFoucs 是否使用分段纹理绘制
 @param tileTexture 是否纹理图片平铺绘制
 @param keepscale 纹理图片是否缩放（tileTexture为YES时生效）
 */
-(void)renderTexturedLinesWithPartPoints:(NSArray*)partPt lineWidth:(CGFloat)lineWidth textureIndexs:(NSArray*)textureIndexs isFocus:(BOOL) isFoucs tileTexture:(BOOL) tileTexture keepScale:(BOOL) keepscale __deprecated_msg("已废弃since 5.0.0，内部无实现，请使用renderMultiTexturedPolyLine");

/**
 使用OpenGLES 按指定单纹理/单色绘制线
 @param points  直角坐标点
 @param pointCount 点个数
 @param lineWidth OpenGLES支持线宽尺寸
 @param textureID 纹理ID,使用- (void)loadStrokeTextureImage:(UIImage *)textureImage;加载
 @param strokeColor 画笔颜色
 @param looped 是否闭合, 如polyline会设置NO, polygon会设置YES.
 @param tileTexture 是否纹理图片平铺绘制
 @param keepScale 纹理图片是否缩放（tileTexture为YES时生效）
 */
- (void)renderTexturedLinesWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount lineWidth:(CGFloat)lineWidth textureID:(GLuint)textureID strokeColor:(UIColor *)strokeColor  looped:(BOOL)looped tileTexture:(BOOL) tileTexture keepScale:(BOOL) keepScale  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 使用OpenGLES 按指定单色/单纹理绘制线 since 5.0.0
 @param points 墨卡托坐标点转换的NSValue
 @param lineWidth OpenGLES支持线宽尺寸
 @param textureID 纹理ID,使用- (void)loadStrokeTextureImage:(UIImage *)textureImage;加载
 @param strokeColor 线颜色
 @param isFoucs 高亮(该属性已废弃)
 @param keepScale 纹理图片是否缩放（(纹理绘制生效)
 @param lineJoinType 拐角衔接方式（默认kBMKLineJoinBevel）
 @param lineCapType 头部处理方式（默认kBMKLineCapButt）
 */
- (void)renderTexturedPolyLineWithPoints:(NSArray <NSValue *> *)points lineWidth:(CGFloat)lineWidth textureID:(GLuint)textureID strokeColor:(UIColor *)strokeColor  isFoucs:(BOOL)isFoucs keepScale:(BOOL)keepScale  lineJoinType:(BMKLineJoinType)lineJoinType lineCapType:(BMKLineCapType)lineCapType  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 使用OpenGLES 分段多纹理/多颜色绘制线 since 5.0.0
 @param partPt 分段墨卡托坐标点转换为的NSValue
 @param lineWidth OpenGLES支持线宽尺寸
 @param textureIndexs 分段纹理索引,使用- (BOOL)loadStrokeTextureImages:(UIImage *)textureImage;加载
 @param isFoucs 高亮(该属性已废弃)
 @param keepScale 纹理图片是否缩放(纹理绘制生效)
 @param lineJoinType 拐角衔接方式（默认kBMKLineJoinBevel）
 @param lineCapType 头尾处理样式(默认kBMKLineCapButt)
 */
-(void)renderMultiTexturedPolyLineWithPartPoints:(NSArray*)partPt lineWidth:(CGFloat)lineWidth textureIndexs:(NSArray<NSNumber *> *)textureIndexs  isFoucs:(BOOL)isFoucs keepScale:(BOOL)keepScale  lineJoinType:(BMKLineJoinType)lineJoinType lineCapType:(BMKLineCapType)lineCapType  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 使用OpenGLES 按指定单色绘制虚线 since 5.0.0
 @param points 墨卡托坐标点转换的NSValue
 @param lineWidth OpenGLES支持线宽尺寸
 @param strokeColor 虚线颜色
 @param lineDashType 虚线样式
 */
- (void)renderDashPolyLineWithPoints:(NSArray <NSValue *> *)points lineWidth:(CGFloat)lineWidth strokeColor:(UIColor *)strokeColor lineDashType:(BMKLineDashType)lineDashType  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 使用OpenGLES 分段多颜色虚线 since 5.0.0
 @param partPt 分段墨卡托坐标点转换为的NSValue
 @param lineWidth OpenGLES支持线宽尺寸
 @param textureIndexs 分段纹理索引,使用colors;加载
 @param lineDashType 虚线样式
 */
-(void)renderMultiDashPolyLineWithPartPoints:(NSArray*)partPt lineWidth:(CGFloat)lineWidth textureIndexs:(NSArray<NSNumber *> *)textureIndexs lineDashType:(BMKLineDashType)lineDashType  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 *使用OpenGLES 绘制区域
 @param points 直角坐标点
 @param pointCount 点个数
 @param fillColor 填充颜色
 @param usingTriangleFan YES对应GL_TRIANGLE_FAN, NO对应GL_TRIANGLES
 */
- (void)renderRegionWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount fillColor:(UIColor *)fillColor usingTriangleFan:(BOOL)usingTriangleFan  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 *使用OpenGLES 绘制区域（支持凹多边形）
 @param points 直角坐标点
 @param pointCount 点个数
 @param fillColor 填充颜色
 @param usingTriangleFan YES对应GL_TRIANGLE_FAN, NO对应GL_TRIANGLES
 */
- (void)renderATRegionWithPoint:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount fillColor:(UIColor *)fillColor usingTriangleFan:(BOOL)usingTriangleFan  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 使用OpenGLES 绘制圆
 @param points 直角坐标点
 @param pointCount 点个数
 @param lineWidth 线宽
 @param fillColor 填充颜色
 @param strokeColor 线颜色
 */
- (void)rendeCircleWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount lineWidth:(CGFloat)lineWidth fillColor:(UIColor *)fillColor strokeColor:(UIColor *)strokeColor  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 使用OpenGLES 绘制Polygon
 @param points 直角坐标点
 @param pointCount 点个数
 @param lineWidth 线宽
 @param fillColor 填充颜色
 @param strokeColor 线颜色
 */
- (void)rendePolygonWithPoints:(BMKMapPoint *)points pointCount:(NSUInteger)pointCount lineWidth:(CGFloat)lineWidth fillColor:(UIColor *)fillColor strokeColor:(UIColor *)strokeColor  __deprecated_msg("已废弃since 6.0.0，内部无实现");

/**
 * 绘制函数(子类需要重载来实现) since 6.0.0 无效
 */
- (void)glRender;

@end
NS_ASSUME_NONNULL_END

