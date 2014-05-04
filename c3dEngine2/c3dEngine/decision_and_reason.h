//
//  decision_and_reason.h
//  c3d
//
//  Created by ck02-084 on 14-4-23.
//
//

#ifndef c3d_decision_and_reason_h
#define c3d_decision_and_reason_h

/*
 --------decision 1
 比较轻的成员（拷贝代价很小）可以使用Type m_member形式。
 较重的成员（拷贝代价较大）应该用Type* m_member形式。从而使其get/set函数开销较小。
 
 通过retain或者addChild来持有的成员，用Type* m_member来定义。其get/set函数分别称为getMember/setMember
 只是引入但不持有的成员，用Type* m_memberPointer来定义。其get/set函数分别称为getMemberPointer/setMemberPointer
 
 */

#endif
