一、名称：从签名中解析公钥技术在以太坊中的应用  
二、简介：   
1、账户、地址、私钥和公钥  
  在以太坊中，账户、地址、私钥（Private Key）和公钥（Public Key）是非常重要的概念。账户扮演着以太坊的中心角色，地址是我们与以太坊系统进行交互的标识，它是以太坊账户与外界进行交互的名字，而私钥与公钥是保护我们账户安全的重要屏障。  
  账户在以太坊中扮演者十分重要的角色，它是以太坊的中心概念。在以太坊中，有两种类型的账户：一种是外部账户（EOAs，Externally Owned Accounts），另一种是合约账户（Contracts Accounts）。当我们提到账户这个术语的时候，我们通常指的是外部账户，当提到合约账户的时候我们通常称其为“合约”。  
不论是外部账户还是合约账户，它们在以太坊中所维护的都是一系列叫做状态对象的实体。这些实体中都拥有状态信息：外部账户存储的是账户的余额，合约账户存储的是余额和合约中的内容。它们存储的这些状态会通过以太坊网络进行更新以及保证数据的一致性。账户是用户在以太坊区块链上创建交易必不可少的一部分。  
账户标识了以太坊网络中每一个参与者的身份，每一笔交易都需要通过账户使用公钥加密进行签名才能够正常进行，这样的话，EVM（以太坊虚拟机）才能够对交易发送者进行验证来确保交易的真实可靠。
一个以太坊地址就代表着一个以太坊账户，地址是账户的标识。对于外部账户来说，地址表示的是该账户公钥的后20字节（通常会以0x开头，例如，0xcd2a3d9f938e13cd947ec05abc7fe734df8dd826，该地址使用的是16进制表示法2）。上述示例中的地址中的字母全部是小写。在EIP553中引入了一种大小写混用的地址表示方法，通过这种表示方法进行表示的地址隐含了一个校验和（checksum）能够验证该地址的有效性.  
  每个账户都由一对钥匙定义，一个私钥（Private Key）和一个公钥（Public Key）。 账户以地址为索引，地址由公钥衍生而来，取公钥的最后20个字节。每对私钥/地址都编码在一个钥匙文件里。以太坊的私钥是一串64位16进制字符（32字节）。它是账户安全最重要的部分，需要妥善保管，如果丢失了私钥也就意味着你的账户丢失了。  
大体来说，地址的生成的流程是：私钥 -> 公钥 -> 地址。因此地址的生成需要三步：  
（1） 生成一个随机的私钥（32字节）  
（2）通过私钥生成公钥（64字节）  
（3）通过公钥得到地址（20字节）。  
2、以太坊的交易流程  
以太坊的转账流程基本是这样的：  
（1）发起交易：指定目标地址和交易金额，以及必需的gas/gasLimit  
（2）交易签名：使用账户私钥对交易进行签名。和比特币一样，也是先对交易本身求hash，再进行签名  
（3）提交交易：验签交易，并将交易提交到交易缓冲池  
（4）广播交易：通知以太坊虚拟机吧交易信息广播给其他节点  
3、以太坊的一个交易到打包的流程  
（1）TxPool从网络上接收到一个交易，发送TxPreEvent事件。  
（2）worker在接收到TxPreEvent事件后，调用update->commitTransactions提交目前收到的交易。  
（3）Work中的commitTransaction负责调用EVM虚拟机执行交易，并返回给Work有关此次交易的Receipt（执行列表）。  
（4）Miner调用Work的commitNewWork，从交易列表中选择交易，组装区块结构。  
（5）Work调用CpuAgent，完成POW工作量证明（打包）。  
（6）一旦区块打包成功，worker广播NewMinedBlockEvent事件。  
4、从签名推导公钥  
签名后的交易发送到以太坊节点后，节点需要从签名交易中还原出公钥(从公钥中单向计算出账号地址)，进而将交易放入交易池中。  
签名过程如下：  
 ![image](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/sm2_1.png))  
推导过程如下：  
 ![image](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/sm2_2.png))  
三、完成人：于晓畅、王婧涵    
四、项目代码说明  
  本项目为在已知签名的情况下推导公钥，故利用了项目二实现的sm2签名及验签，再加上def pk_fron_signature()函数，共同构成了本项目的完整代码。  
  为实现椭圆曲线的运算，需要一些基本的函数，如素数检测、字节和int的转换、求最大公约数、求乘法逆元等，本代码的前面部分实现了这些基础函数。其后定义了椭圆曲线密码类，用以实现一般的ECC运算：加法、乘法、求反等。再然后定义了SM2类继承ECC，实现SM2算法的签名、验签等。最后是与本项目直接相关的从签名推导公钥的函数，利用了项目说明里的推导过程，得出推导式后代码实现之。  

五、运行指导：利用PyCharm在安装了所需模块的前提下直接run即可  
六、运行截图  
 ![image](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/sm2_3.png))    
与设置的公钥进行对比：  
 ![image](https://github.com/yuuu218/Innovation-pioneering/blob/main/image/sm2_4.png))    
其中PA为公钥，对比发现一致。  
七、具体贡献说明  
于晓畅：完成代码  
王婧涵：搜集资料  