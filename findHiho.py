#!/usr/bin/python
#  -*- coding:utf-8 -*-

#http://www.cnblogs.com/rollenholt/archive/2012/04/23/2466179.html  python文件操作

import requests ##实现爬虫
from bs4 import BeautifulSoup   ##解析网页html文件，比正则表达式简单
import re   ##重整字符串，筛选
import os


nowFolder=os.getcwd()
allFolder=os.listdir(nowFolder)

for aFloder in allFolder:
    print '-' * 100
    print '-' * 100
    matchUsefulWord = re.match('a', aFloder)
    if matchUsefulWord:
        numHiho=aFloder.split('a')[-1]
        print numHiho

        url='https://hihocoder.com/problemset/problem/'+numHiho
        r = requests.get(url, allow_redirects=False)  ##禁止跳转网页
        text = r.text
        print r.url, r.status_code
        soup = BeautifulSoup(text, "lxml")
        bodyWords = soup.body

        aFilePath = nowFolder + '/' + aFloder + '/'+'subject.html'
        print '-' * 100
        print 'downloading to:',aFilePath
        with open(aFilePath, 'wb') as filedown:

            ## 保持汉字
            filedown.write('<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"> <p>'
                           +url+'</p>')

            ## 输入题目
            for title in bodyWords.findAll('h3'):  ##title=<h3 class='...'>lalala</h3>
                if re.search('#', title.string):
                    filedown.write('p'+title.string.encode("utf-8")+'</p>')

            ## 输入输出
            input = 0
            output = 0
            for mark in bodyWords.findAll('dt'):
                if re.search('Sample Input',mark.string) and input==0:
                    filedown.write('<p> input: </p>')
                    filedown.write(mark.next_sibling.next_sibling.encode())
                    input=1
                if re.search('Sample Output',mark.string) and output==0:
                    filedown.write('<p> output: </p>')
                    filedown.write(mark.next_sibling.next_sibling.encode())
                    output=1

            ## 题目介绍
            for passage in bodyWords.findAll('p'):
                filedown.write(passage.encode("utf-8"))


        filedown.close()