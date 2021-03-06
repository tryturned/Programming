<!--
 * @Author: taobo
 * @Date: 2020-11-10 21:22:16
 * @LastEditTime: 2020-11-27 19:18:33
-->
# 计算机网络 - HTTPS与HTTP常见面试题  

<!-- toc -->
* [计算机网络 - HTTPS与HTTP常见面试题](#计算机网络---HTTPS与HTTP常见面试题)
    * [1.HTTP的缺点](#1-HTTP的缺点)
    * [2.加密处理](#2-加密处理)
    * [3.SSL](#3-SSL)
    * [4.Session 管理及 Cookie 应用](#4-Session-管理及-Cookie-应用)
    * [5.HTTP 1.1 与 HTTP 2.0 差异](#5-HTTP1.1与HTTP2.0差异)
    * [6.GET 和 POST 报文上的区别](#6-GET-和-POST-报文上的区别)
    * [7.HTTP请求方法](#7-请求方法)
<!-- toc -->  

## 1. HTTP的缺点
- 通信使用明文（不加密），内容可能会被窃听
- 不验证通信方的身份，因此有可能遭遇伪装
- 无法证明报文的完整性，所以有可能已遭篡改
## 2. 加密处理  
- 通信的加密：HTTP 协议中没有加密机制，但可以通过和 SSL或 TLS（安全层传输协议）的组合使用，加密 HTTP的通信内容。 
- 内容的加密：将参与通信的内容本身加密的方式。由于 HTTP 协议中没有加密机制，那么就对 HTTP 协议传输的内容本身加密。即把 HTTP 报文里所含的内容进行加密处理。
- 第二种方式不同于 SSL 或 TLS 将整个通信线路加密处理，所以内容仍有被篡改的风险。 
## 3. SSL  
![ssl](https://gitee.com/windyGOlife/cmianshi/raw/master/HTTP/Photo/ssl.png)
HTTPS 比 HTTP 要慢 2 到 100 倍。SSL 的慢分两种。一种是指通信慢。另一种是指由于大量消耗 CPU 及内存等资源，导致处理速度变慢。   
和使用 HTTP 相比，网络负载可能会变慢 2 到 100 倍。除去和 TCP 连接、发送 HTTP 请求，响应以外，还必须进行 SSL 通信， 因此整体上处理通信量不可避免会增加。  
另一点是 SSL 必须进行加密处理。在服务器和客户端都需要进行加密和解密的运算处理。因此从结果上讲，比起 HTTP 会更多地 消耗服务器和客户端的硬件资源，导致负载增强。  
## 4. Session 管理及 Cookie 应用 
![cook_see](https://gitee.com/windyGOlife/cmianshi/raw/master/HTTP/Photo/cookie_session.png)  
鉴于 HTTP 是无状态协议，之前已认证成功的用户状态无法通过协议层面保存下来。即无法实现状态管理，因此即使当该用户下一次继续访问，也无法区分他与其他的用户。于是我们会使用 Cookie 来管理Session，以弥补 HTTP 协议中不存在的状态管理功能。
## 5. HTTP1.1与HTTP2.0差异
- HTTP/2.0 采用二进制格式而非文本格式
- HTTP/2.0 是完全多路复用的，而非有序并阻塞的——只需一个连接即可实现并行
- 使用报头压缩，HTTP/2.0 降低了开销
- HTTP/2.0 让服务器可以将响应主动“推送”到客户端缓存中  
需要明白的几个点是：  
（1）HTTP/2.0 为什么是二进制传输？   
比起像HTTP/1.x这样的文本协议，二进制协议解析起来更高效、“线上”更紧凑，更重要的是错误更少。  
（2）为什么 HTTP/2.0 需要多路传输?  
HTTP/1.x 有个问题叫线端阻塞(head-of-line blocking), 它是指一个连接(connection)一次只提交一个请求的效率比较高, 多了就会变慢。 HTTP/1.1 试过用流水线(pipelining)来解决这个问题, 但是效果并不理想(数据量较大或者速度较慢的响应, 会阻碍排在他后面的请求). 此外, 由于网络媒介(intermediary )和服务器不能很好的支持流水线, 导致部署起来困难重重。而多路传输(Multiplexing)能很好的解决这些问题, 因为它能同时处理多个消息的请求和响应; 甚至可以在传输过程中将一个消息跟另外一个掺杂在一起。所以客户端只需要一个连接就能加载一个页面。  
（3）服务器推送的好处是什么？   
当浏览器请求一个网页时，服务器将会发回HTML，在服务器开始发送JavaScript、图片和CSS前，服务器需要等待浏览器解析HTML和发送所有内嵌资源的请求。服务器推送服务通过“推送”那些它认为客户端将会需要的内容到客户端的缓存中，以此来避免往返的延迟。     
 
【推荐阅读】 [HTTP 2.0与HTTP 1.1区别](https://www.cnblogs.com/frankyou/p/6145485.html) ，[HTTP1.0、HTTP1.1和HTTP2.0 的区别
](https://juejin.im/entry/5981c5df518825359a2b9476)  
## 6. GET 和 POST 报文上的区别
GET 和 POST 方法没有实质区别，只是报文格式不同。在RFC文档约定之下，GET 用于获取信息，是无副作用的，且可缓存。POST 用于修改服务器上的数据，有副作用，不可缓存。   
- 传参方式。GET默认将参数写在URI里面，即写在 ? 后面，用 & 分割。
- POST 方法比 GET 方法安全？答案其实是否定的，毕竟除非使用HTTPS，否则仍旧是不安全的
- GET 方法的长度限制是怎么回事？  
HTTP 协议没有 Body 和 URL 的长度限制，对 URL 限制的大多是浏览器和服务器的原因。服务器是因为处理长 URL 要消耗比较多的资源，为了性能和安全（防止恶意构造长 URL 来攻击）考虑，会给 URL 长度加限制。   
- POST 方法会产生两个 TCP 数据包？  
一般配合3XX状态码重定向使用，但官方文档中没有明确说明 POST 会产生两个 TCP 数据包，而且实际测试(Chrome)发现，header 和 body 不会分开发送。所以，header 和 body 分开发送是部分浏览器或框架的请求方法，不属于 post 必然行为。    

【推荐阅读】[都 2019 年了，还问 GET 和 POST 的区别](https://blog.fundebug.com/2019/02/22/compare-http-method-get-and-post/)

## 7. 请求方法
HTTP/1.1协议中共定义了八种方法（也叫“动作”）来以不同方式操作指定的资源：
### GET
向指定的资源发出“显示”请求。使用GET方法应该只用在读取资料，而不应当被用于产生“副作用”的操作中，例如在网络应用程序中。其中一个原因是GET可能会被网络爬虫等随意访问。浏览器直接发出的GET只能由一个url触发。GET上要在url之外带一些参数就只能依靠url上附带。
### HEAD
与GET方法一样，都是向服务器发出指定资源的请求。只不过服务器将不传回资源的本文部分。它的好处在于，使用这个方法可以在不必传输全部内容的情况下，就可以获取其中“关于该资源的信息”（元信息或称元数据）。
### POST
**向指定资源提交数据，请求服务器进行处理**（例如提交表单或者上传文件）。数据被包含在请求本文中。这个请求可能会创建新的资源或修改现有资源，或二者皆有。每次提交，表单的数据被浏览器用编码到HTTP请求的body里。浏览器发出的POST请求的body主要有两种格式，一种是application/x-www-form-urlencoded用来传输简单的数据，大概就是"key1=value1&key2=value2"这样的格式。另外一种是传文件，会采用multipart/form-data格式。采用后者是因为application/x-www-form-urlencoded的编码方式对于文件这种二进制的数据非常低效。
### PUT
向指定资源位置上传其最新内容。
### DELETE
请求服务器删除Request-URI所标识的资源。
### TRACE
回显服务器收到的请求，主要用于测试或诊断。
### OPTIONS
这个方法可使服务器传回该资源所支持的所有HTTP请求方法。用'*'来代替资源名称，向Web服务器发送OPTIONS请求，可以测试服务器功能是否正常运作。
### CONNECT
HTTP/1.1协议中预留给能够将连接改为隧道方式的代理服务器。通常用于SSL加密服务器的链接（经由非加密的HTTP代理服务器）。  


方法名称是区分大小写的。当某个请求所针对的资源不支持对应的请求方法的时候，服务器应当返回状态码405（Method Not Allowed），当服务器不认识或者不支持对应的请求方法的时候，应当返回状态码501（Not Implemented）。