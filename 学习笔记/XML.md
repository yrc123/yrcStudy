# XML

## XML基本语法

### XML声明

```xml
<? xml version="1.0"?>
```

- version：版本号
- standalone：指明文档是否独立
- encoding：字符集，默认UTF-8

### XML标记命名规则

- 首字符是英文字母、汉字或_，后跟数字和其他字符。
- 严格区分英文字母的大小写。
- 不能独立使用数字作为名称。
- 不能使用“<”,”>”,”?”,”/”,”&”,”+”,”*”等符号作为标记名。

### 空标记

- 非空标记

  - ```xml
    <test>string</test>
    ```

- 空标记

  - ```xml
    <!--有两种表示方式-->
    <test name="测试"></test>
    <test name="测试" />
    ```

### 属性

- 属性必须定义在起始标记内。
- 可以由字母、数字、中文及下划线组成，但**必须以字母、中文或下划线**开头。
- 属性名区分大小写。
- 属性值必须使用单引号或双引号。
- 如果属性值中要使用左尖括号“<”、右尖括号“>”、连接符号“&”、单引号“‘”或双引号“””时，必须使用字符引用或实体引用。

### 实体

- XML文档可以包含若干个存储单元，这些存储单元叫做实体，由实体名称来标识。
- 在XML文档中，所有文本都会被解析器解析。但如果在实际运用中，需要在XML文档内引用左尖括号“<”、右尖括号“>”、连接符号“&”、单引号“‘”或双引号“””等特殊符号，可以用XML预定义实体来解决。
#### 预定义实体

>\&:  \&amp;
> ‘ :  \&apos;
> \>:  \&gt;
> \<:  \&lt;
> “:  \&quot;

#### 一般实体

- 声明

  - ```xml
    <!ENTITY 实体名 实体定义>
    ```

- 引用方法

  - ```xml
    &实体名
    ```

- 例如

  - ```xml
    <!ENTITY qhPress "清华大学出版社">
    <press>&qhPress;</press>
    ```

#### 参数实体

- 声明

  - ```xml
    <!ENTITY %实体名 实体定义>
    ```

- 引用方法

  - ```xml
    %实体名
    ```

- 例如

  - ```xml
    <!ENTITY %dataType "(#PCDATA)">
    <!--
    	<!ELEMENT name 元素名>
    	用来自定义元素
    -->
    <!ELEMENT name %dataType;>
    ```

#### 内部实体

- 在文档内部进行定义

- 例如

  - ```xml
    <?xml version="1.0" ?>
        <!DOCTYPE books[
           <!ENTITY qhPress "清华大学出版社">
         ]>
        <books>
            …..
        </books>
    
    ```

#### 外部实体

- 在文档外进行定义

- 定义格式

  - ```xml
    <!ENTITY 实体名 SYSTEM/PUBLIC URI NDATA 类型名>
    ```

- 例如

  - ```xml
    <!ENTITY fact SYSTEM "http://www.a.com/fact.xml">
    <!ENTITY src SYSTEM "pic.gif" NDATA GIF>
    ```



## XML Schema|XML模式

### 什么是XML Schema

- 用于定义XML文档和内容的文档
- 作用与DTD一样

### Schema与DTD的异同

- DTD是用一种与XML不同的语法编写，而Schema是用一种类似XML的语言
- Schema支持丰富的数据类型
- Schema支持命名空间

### XML Schema基本结构

#### Microsoft XML Schema模式

```xml
<Schema name=“schema-name” xmlns=“namespace”>
	……
</Schema>
```

- 根元素为Schema
- 一般的命名空间
  - ` xmlns="urn:schemas-microsoft-com:xml-data"`
  - `Xmlns:dt=“urn:schemas-microsoft-com:datatypes”`

#### W3C XML Schema模式

```xml
<Schema xmlns:xsd=“namespace”>
	……
</Schema>
```

- 根元素为Schema
- 命名空间为
  - `xmlns:xsd="http://www.w3.org/2001/XMLSchema"`

#### 实例

```xml
<?xml version="1.0"?>
<!--W3C XML Schema模式-->
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema">
	<!--
			如果要使用预定义的标记，要加上命名空间
			如：要定义为string类型，在string前面要加上xsd命名空间
					否则被认为为用户自定义类型
	-->
    <xsd:element name="员工">
		<xsd:complexType>
			<xsd:sequence>
				<xsd:element name="姓名" type="xsd:string"/>
				<xsd:element name="性别" type="xsd:string"/>a
				<xsd:element name="出生日期" type="xsd:date"/>
			</xsd:sequence>
		</xsd:complexType>
	</xsd:element>
</xsd:schema>
```

### W3C XML Schema的数据类型

#### 简单类型

- 元素中仅包含文本数据，且不包含属性：

  - ```xml
    <xsd:simpleType  name=名称 id=ID>
        	<!--
    			name仅仅是简单类型的名称，与元素的名字无关
    		-->
    		<xsd:restriction|xsd:list|xsd:union>
                ……
    </xsd:simpleType>
    ```

##### 原子类型

- 使用xsd:restriction限制简单类型

  - ```xml
    <xsd:element name="membership_ID">
        	<!--包含在element元素内，代表作用于只在membership_ID内-->
    		<xsd:simpleType>
                <!--base属性来定义数据类型-->
    			<xsd:restriction base="xsd:string">
                    <!--对类型的限制-->
    				<xsd:pattern value="\d{5}(-\d{4})?"/>
    			</xsd:restriction>
    		</xsd:simpleType>
    	</xsd:element>
    ```

##### 列表类型

- 格式

  - ```xml
    <xsd:list itemType="元素类型">
    <!--例如-->
    <xsd:simpleType name="listofNumber">
          <xsd:list itemType="xsd:decimal">
    </xsd:simpleType>
    ```

##### 联合类型

- 格式

  - ```xml
    <xsd:union memberType="元素类型 元素类" >
    <!--例如-->
    <xsd:simpleType name="成绩">
          <xsd:union memberType="学生 分数">
    </xsd:simpleType>
    
    ```

##### 枚举类型

- 格式

  - ```xml
    <xs:simpleType name="gender">
    	<xs:restriction base="xs:string">
        	<xs:enumeration value="男"></xs:enumeration>  				
       		<xs:enumeration value="女"></xs:enumeration> 		
        </xs:restriction>
    </xs:simpleType> 
    ```

#### 复杂类型

- 只含元素

- 只含文本

- 空元素

- 混合类型

```xml
<?xml version="1.0"?>
<!--例子-->
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema">
   <xsd:element name="图书">
    	<xsd:complexType>
			<xsd:sequence>
				<xsd:element name="书名" type="xsd:string"/>
			

￼
<?xml version="1.0"?>
<!--例子-->
<xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema">
   <xsd:element name="图书">
        <xsd:complexType>
            <xsd:sequence>
                <xsd:element name="书名" type="xsd:string"/>
                <xsd:element name="作者" type="xsd:string"/>
                <xsd:element name="售价" type="xsd:decimal"/>
                <xsd:element name="简介" type="xsd:string"/>
                <xsd:element name="出版信息" minOccurs="0" maxOccurs="1">
                <!--minOccurs和maxOccurs用来定义出现次数，"unbounded"可以代表无限次-->
                    <xsd:complexType>
                        <xsd:sequence>
                            <xsd:element name="出版社" type="xsd:string"/>
                            <xsd:element name="版次" type="xsd:date"/>
                        </xsd:sequence>
                     </xsd:complexType>
                </xsd:element>
            </xsd:sequence>
            <xsd:attribute name="isbn" type="xsd:string"/>
        </xsd:complexType>
    </xsd:element>
</xsd:schema>	<xsd:element name="作者" type="xsd:string"/>
				<xsd:element name="售价" type="xsd:decimal"/>
				<xsd:element name="简介" type="xsd:string"/>
				<xsd:element name="出版信息" minOccurs="0" maxOccurs="1">
        		<!--minOccurs和maxOccurs用来定义出现次数，"unbounded"可以代表无限次-->
					<xsd:complexType>
			    		<xsd:sequence>
			        		<xsd:element name="出版社" type="xsd:string"/>
			        		<xsd:element name="版次" type="xsd:date"/>
			     		</xsd:sequence>
		             </xsd:complexType>
				</xsd:element>
	  		</xsd:sequence>
            <xsd:attribute name="isbn" type="xsd:string"/>
        </xsd:complexType>
    </xsd:element>
</xsd:schema>
```

### 引用XML Schema 

```xml
<!--引用 Microsoft XML Schema-->
<根元素名  xmlns=“x-schema:schema文档名” />

```



- Schema文档中未定义目标命名空间

  - ```xml
    <员工 xmlns:xsd(名称空间前缀,可随意起名)="http://www.w3.org/2001/XMLSchema-instance"
           xsd:noNamespaceSchemaLocation="未定义名称空间的Schema文件地址.xsd">
    ……
    </员工>
    ```

- 如果Schema文档中已经定义目标命名空间
  - ```xml
    <员工 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
           xsi:SchemaLocation="http://名称空间地址  Schema文件地址.xsd">
    ……
         xmlns=http://名称空间地址 >
    ……
    </员工>
    ```


## XSL

### 概述

- XSL是可扩展样式表语言，包含3个内容：XSLT，XPath，XSL格式化对象语言（XSL-FO）
- XSL将文档和内容和表示形式分离
- 将同一个内容转化成不同格式的方法，如将XML转换为HTML

```xml
<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/TR/WD-xsl">
    <!--设置模板当前位置为根目录/-->
	<xsl:template match="/">
		<html>
			<head>
				<title>
                    <!--选择当前目录下的title-->
					<xsl:value-of select="title"/>
				</title>
			</head>
			<body>
                <!--选择doc下的所有chapter-->
                <!--apply-templates 对select内容应用模板，匹配到template match="chapter"-->
				<xsl:apply-templates select="doc/chapter"/>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="chapter">
             <center>
                <font size="+3">
                    <xsl:value-of select="title"/> 
                </font>
             </center>
	       <p><xsl:value-of select="section"/></p>
	</xsl:template>
</xsl:stylesheet>
```

## Xlink和XPointer技术

#### XLink

- 在XML文档中使用XLink，必须明确XLink的命名空间：`xmlns:xlink="http://www.w3.org/1999/xlink"` 


| 属性          | 值                                                     | 描述                                |
| ------------- | ------------------------------------------------------ | ----------------------------------- |
| xlink:actuate | onLoad 、onRequest、other                              | 定义何时读取和显 示被链接的资源。   |
| xlink:href    | *URL*                                                  | 要链接的 URL。                      |
| xlink:show    | embed 、new 、 replace                                 | 在何处打开链接。 replace 是默认值。 |
| xlink:type    | simple 、extended 、 locator 、arc 、resource  、title | 链接的类型                          |
| xlink:role    | 字符串                                                 | 描述链接的功能                      |
| xlink:title   | 字符串                                                 | 向用户描述链接的 相关信息           |

- Simple Link
  - 计出接近基本HTML的链接功能
  - 