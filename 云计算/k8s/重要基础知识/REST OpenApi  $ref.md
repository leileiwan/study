<!-- TOC -->

- [1. REST 介绍](#1-rest-介绍)
    - [1.1 为什么要使用RESTful 结构](#11-为什么要使用restful-结构)
- [2 OpenAPI](#2-openapi)
    - [2.1 Swagger(工具)](#21-swagger工具)
- [3. $ref](#3-ref)

<!-- /TOC -->
# 1. REST 介绍
REST不是"rest"这个单词，而是Resource Representational State Transfer的缩写：通俗来讲就是：资源在网络中以某种表现形式进行状态转移。

REST描述的是在网络中client和server的一种交互形式；REST本身不实用，实用的是如何设计 RESTful API（REST风格的网络接口）。REST它是一种架构风格，腾讯公司或其他公司建立API时要遵守的一种规则/风格，当然也有其他规则可以用。

## 1.1 为什么要使用RESTful 结构
大家都知道"古代"网页是前端后端融在一起的。在之前的桌面时代问题不大，但是近年来移动互联网的发展，各种类型的Client层出不穷，RESTful可以通过一套统一的接口为Web,iOS和Android提供服务。另外对于广大平台来说，比如Facebook，微博开放平台，微信公共平台等，它们不需要有显式的前端，只需要一套提供服务的接口。

1.客户-服务器（Client-Server）客户端服务器分离
提高用户界面的便携性（操作简单）
通过简化服务器提高可伸缩性（高性能，低成本）
允许组件分别优化（可以让服务端和客户端分别进行改进和优化）

2.无状态（Stateless）
从客户端的每个请求要包含服务器所需要的所有信息
优点:
提高可见性（可以单独考虑每个请求）
提高了可靠性（更容易从局部故障中修复）
提高可扩展性（降低了服务器资源使用）

3.缓存（Cachable）
服务器返回信息必须被标记是否可以缓存，如果缓存，客户端可能会重用之前的信息发送请求。
优点:减少交互次数,减少交互的平均延迟。

4.分层系统（Layered System）
系统组件不需要知道与他交流组件之外的事情。封装服务，引入中间层。
优点:限制了系统的复杂性,提高可扩展性。

5.统一接口（Uniform Interface）
优点:提高交互的可见性,鼓励单独改善组件。

6.支持按需代码（Code-On-Demand）
优点:提高可扩展性

#  2 OpenAPI
OpenAPI规范（以前称为Swagger规范）是REST API的API描述格式。
An OpenAPI file allows you to describe your entire API, including:
* Available endpoints (/users) and operations on each endpoint (GET /users, POST /users)
* Operation parameters Input and output for each operation
* Authentication methods
* Contact information, license, terms of use and other information.

## 2.1 Swagger(工具)
refence: https://swagger.io/docs/specification/about/

Swagger is a set of open-source tools built around the OpenAPI Specification that can help you design, build, document and consume REST APIs. The major Swagger tools include:

* Swagger Editor – browser-based editor where you can write OpenAPI specs.
* Swagger UI – renders OpenAPI specs as interactive API documentation.
* Swagger Codegen – generates server stubs and client libraries from an OpenAPI spec.

# 3. $ref
When you document an API, it is common to have some features which you use across several of API resources. In that case, you can create a snippet(片段) for such elements in order to use them multiple times when you need it. （相当于引用字段）。
To reference a definition, use the $ref keyword。
```
$ref: 'reference to definition'
```
```
components:
  schemas:
    User:
      properties:
        id:
          type: integer
        name:
          type: string

```
```
responses:
  '200':
    description: The response
    schema: 
      $ref: '#/components/schemas/User'
```

