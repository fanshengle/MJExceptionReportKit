//
//  BMKUtilsVersion.h
//  UtilsComponent
//
//  Created by wzy on 15/9/9.
//  Copyright © 2015年 baidu. All rights reserved.
//

#ifndef BMKUtilsVersion_h
#define BMKUtilsVersion_h

#import <UIKit/UIKit.h>

/**
 *重要：
 *utils组件的版本和base组件的版本必须一致，否则不能正常使用
 */

/**
 *获取当前地图API utils组件 的版本号
 *return  返回当前API utils组件 的版本号
 */
FOUNDATION_EXTERN NSString* BMKGetMapApiUtilsComponentVersion(void);

/**
 *检查utils组件的版本号是否和base组件的版本号一致
 *return    版本号一致返回YES
 */
UIKIT_EXTERN BOOL BMKCheckUtilsComponentIsLegal(void);


#endif /* BMKUtilsVersion_h */
