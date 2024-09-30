[PYTHON]
import os
import re
import time
from datetime import datetime
from xml.etree import ElementTree
from xml.etree.ElementTree import Element, SubElement
from xml.dom import minidom

class SVNInfo:
    def __init__(self, url, revision):
        self.url = url
        self.revision = revision

    def create_xml(self):
        root = Element('info')
        SubElement(root, 'entry', attrib={'url': self.url})
        SubElement(root, 'commit', attrib={'revision': str(self.revision)})
        return root

    @staticmethod
    def from_xml(root):
        url = root.find('entry').attrib['url']
        revision = int(root.find('commit').attrib['revision'])
        return SVNInfo(url, revision)

class SVNLog:
    def __init__(self, path, revision, author, date):
        self.path = path
        self.revision = revision
        self.author = author
        self.date = date

    def create_xml(self):
        root = Element('logentry')
        SubElement(root, 'msg').text = ''
        SubElement(root, 'changed-paths', attrib={'action': 'M', 'kind': 'file'}).text = self.path
        SubElement(root, 'commit', attrib={'revision': str(self.revision)}).text = ''
        SubElement(root, 'author').text = self.author
        SubElement(root, 'date').text = time.strftime('%Y-%m-%dT%H:%M:%SZ', self.date)
        return root

    @staticmethod
    def from_xml(root):
        path = root.find('changed-paths').attrib['path']
        revision = int(root.find('commit').attrib['revision'])
        author = root.find('author').text
        date = datetime.strptime(root.find('date').text[:-1], '%Y-%m-%dT%H:%M:%SZ')
        return SVNLog(path, revision, author, date)

class SVNClient:
    def __init__(self):
        self.xml_parser = ElementTree.XMLParser()

    def info(self, path):
        url = None
        revision = -1
        root = ElementTree.Element('info')
        try:
            os.system("svn info {}".format(path))
            output = os.popen("svn info {} --xml".format(path)).read()
            root = self.xml_parser.feed(output).getroot()
            url = root.find('entry').attrib['url']
            revision = int(root.find('commit').attrib['revision'])
        except:
            pass
        return SVNInfo(url, revision)

    def log(self, path):
        logs = []
        root = ElementTree.Element('log')
        try:
            os.system("svn log {}".format(path))
            output = os.popen("svn log {} --xml -v".format(path)).read()
            for line in output.split('\n'):
                if line.strip():
                    root = self.xml_parser.feed(line).getroot()
                    logs.append(SVNLog.from_xml(root))
        except:
            pass
        return logs

class SVNUtils:
    def __init__(self):
        self.client = SVNClient()

    def get_info(self, path):
        info = None
        try:
            info = self.client.info(path)
        except Exception as e:
            pass
        return info

    def get_log(self, path):
        logs = []
        try:
            logs = self.client.log(path)
        except Exception as e:
            pass
        return logs

def main():
    path = "C:\\Users\\Administrator\\Desktop"
    svn_utils = SVNUtils()
    info = svn_utils.get_info(path)
    print("URL: {}".format(info.url))
    print("Revision: {}".format(info.revision))
    logs = svn_utils.get_log(path)
    for log in logs:
        print("Path: {}, revision: {}, author: {}, date: {}".format(log.path, log.revision, log.author, log.date))

if __name__ == "__main__":
    main()
[/PYTHON]
