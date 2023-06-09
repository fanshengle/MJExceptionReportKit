/*
 *  BMKPoiSearchOption.h
 *  BMapKit
 *
 *  Copyright 2013 Baidu Inc. All rights reserved.
 *
 */

#import <BaiduMapAPI_Base/BMKTypes.h>
#import "BMKRouteSearchType.h"
/// 路线查询基础信息类
@interface BMKBaseRoutePlanOption : NSObject

/// 检索的起点，可通过关键字、坐标两种方式指定。cityID可参考官方网站-开发文档-开发资源
/// 优先级：pt > cityID+name > cityName+name
@property (nonatomic, strong) BMKPlanNode *from;

/// 检索的起点，可通过关键字、坐标两种方式指定。cityID可参考官方网站-开发文档-开发资源
/// 优先级：pt > cityID+name > cityName+name
@property (nonatomic, strong) BMKPlanNode *to;

@end


/// 步行查询基础信息类
@interface BMKWalkingRoutePlanOption : BMKBaseRoutePlanOption
@end


/// 驾车查询基础信息类
@interface BMKDrivingRoutePlanOption : BMKBaseRoutePlanOption

/// 驾车途经点
@property (nonatomic, copy) NSArray <BMKPlanNode *> *wayPointsArray;

///驾车检索策略，默认使用BMK_DRIVING_TIME_FIRST
@property (nonatomic, assign) BMKDrivingPolicy drivingPolicy;

///驾车检索获取路线每一个step的路况，默认使用BMK_DRIVING_REQUEST_TRAFFICE_TYPE_NONE
@property (nonatomic, assign) BMKDrivingRequestTrafficType drivingRequestTrafficType;

@end


/// 公交查询基础信息类
@interface BMKTransitRoutePlanOption : BMKBaseRoutePlanOption

///城市名，用于在哪个城市内进行检索
@property (nonatomic, copy) NSString *city;

///公交检索策略，默认使用BMK_TRANSIT_TIME_FIRST
@property (nonatomic, assign) BMKTransitPolicy transitPolicy;

@end


/// 公共交通路线查询基础信息类（支持市内和跨城）(注：起终点城市不支持cityId)
@interface BMKMassTransitRoutePlanOption : BMKBaseRoutePlanOption

///分页索引，可选，默认为0(从0开始)
@property (nonatomic, assign) NSUInteger pageIndex;

///分页数量，可选，默认为10，取值范围[1,10]
@property (nonatomic, assign) NSUInteger pageCapacity;

///市内公交换乘策略策略，可选，默认使用BMK_MASS_TRANSIT_INCITY_RECOMMEND
@property (nonatomic, assign) BMKMassTransitIncityPolicy incityPolicy;

///跨城公交换乘策略，可选，默认使用BMK_MASS_TRANSIT_INTERCITY_TIME_FIRST
@property (nonatomic, assign) BMKMassTransitIntercityPolicy intercityPolicy;

///跨城交通方式策略，可选，默认使用BMK_MASS_TRANSIT_INTERCITY_TRANS_TRAIN_FIRST
@property (nonatomic, assign) BMKMassTransitIntercityTransPolicy intercityTransPolicy;

@end


/// 骑行查询基础信息类
@interface BMKRidingRoutePlanOption : BMKBaseRoutePlanOption

/// 骑行类型（0：普通骑行，1：电动车骑行），默认是普通骑行
@property (nonatomic, assign) NSInteger ridingType;

/// 骑行途经点（目前只支持一个途径点） since 6.5.2
@property (nonatomic, copy) NSArray <BMKPlanNode *> *wayPointsArray;

@end


/// 室内路线规划查询基础信息类
@interface BMKIndoorRoutePlanOption : NSObject

///检索的起点
@property (nonatomic, strong) BMKIndoorPlanNode *from;

///检索的终点
@property (nonatomic, strong) BMKIndoorPlanNode *to;

@end
