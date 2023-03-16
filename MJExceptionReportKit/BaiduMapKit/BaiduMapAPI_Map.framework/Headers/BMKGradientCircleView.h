//
//  BMKGradientCircleView.h
//  MapComponent
//
//  Created by zhangbaojin on 2022/7/4.
//  Copyright © 2022 Baidu. All rights reserved.
//

#import "BMKCircleView.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 渐变规则如下:
 * （0 ~ radiusWeight * radius） 该部分颜色从 centerColor 渐变至 centerColor + colorWeight * (sideColor - centerColor)；
 * （radiusWeight * radius ~ radius）该部分间颜色从 centerColor + colorWeight * (sideColor - centerColor) 渐变至 sideColor；
 */

/// 该类用于定义圆对应的渐变View since 6.5.4
/// 注意：渐变圆不支持镂空及fillColor
@interface BMKGradientCircleView : BMKCircleView

/// 中心颜色
@property (nonatomic, strong) UIColor *centerColor;

/// 边缘颜色
@property (nonatomic, strong) UIColor *sideColor;

/// 半径权重
/// 取值范围（0.0, 1.0），默认 0.5
@property (nonatomic, assign) float radiusWeight;

/// 颜色权重
/// 取值范围（0.0, 1.0），默认 0.2
@property (nonatomic, assign) float colorWeight;

@end

NS_ASSUME_NONNULL_END
