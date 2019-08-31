# shahada
<b>shahada</b> is the library for HTTP parser<br>
shahada http parser can be compiled as a binary by using</br> 
<b>#(prompt)</b>make bin <br>
This creates folder bin and inside this folder the binary named shahada is generated.<br>
It also can be static library by using<br> 
<b>#(prompt)</b>make lib <br>
The library is built in lib folder.<br>

Alos both binaray ans lib can be built simultaneously by using below<br> 
<b>#(prompt)</b>make<br>

<b>This Library doesn't support chunked with extension payload</b>
<H1>How to use this library</H1><br>
<ol>
<li>void *shahadaHttpParserStart(char *pIn);</li>
<li>void shahadaHttpParserEnd(void *handle);</li>
<li>char *shahadaGetFieldValue(char *field_name, void *msg);</li>
<li>char *shahadaGetUri(void *pMsg);</li>
<li>char *shahadaGetQsParamValue(char *qsParamName, void *pMsg);</li>
<li>char *shahadaGetReasonPhrase(void *pMsg);</li>

<li>int shahadaGetStatusCode(void *pMsg);</li>
<li>int shahadaGetMethod(void *pMsg);</li>
<li>int shahadaGetProtocol(void *pMsg);</li>

<li>void shahadaHttpParserEnd(void *pIn);</li>

<li>char *shahadaGetBody(int chunkNumber, void *pIn, int *chunkedLen);</li>
</ol>
