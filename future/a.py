import os


class 文件对象:
    def __init__(self, item_path, item_name):
        self.path = item_path
        self.name = item_name

    def __str__(self):
        n = self.path.count('\\')
        # return "┠{} {}\n".format('━'*n,self.name)
        return '{}<a href={}>{}</a><br>\n<br>\n'.format("--"*2*(n-1), self.path.replace(' ', '%20'), self.name)


class 文件夹对象:
    def __init__(self, item_path, content=None):
        # print('before:',item_path)
        self.path = item_path
        if content is None:
            self.content = []
        if os.path.isdir(self.path):
            self.name = self.path.split('\\')[-1]
        content = []
        if self.name:
            def key_func(x):
                try:
                    return int(x.split('、')[0])
                except (TypeError, ValueError) as err:
                    return 999

            # temp_list=sorted(os.listdir(self.path),key=key_func)

            for item in sorted(os.listdir(self.path), key=key_func):
                temp_path = os.path.join(self.path, item)
                # print(temp_path)
                if os.path.isdir(temp_path):
                    # print(temp_path)
                    content.append(文件夹对象(temp_path, item))
                else:
                    content.append(文件对象(temp_path, item))

        self.content = content

    def __str__(self):
        n = self.path.count('\\')
        #output="┏{} 【{}】\n".format('━'*n,self.name)
        output = '{}【{}】<br>\n'.format(
            "--"*2*(n-1), self.name)
        for item in self.content:
            output += "{!s}".format(item)
        return output


class 文件统计:
    def __init__(self, path='.'):
        self.path = path
        self.HTML_TEMP = ('<!DOCTYPE HTML>\n'
                          '<html>\n<head>\n<meta charset="utf-8">\n<title>文件目录</title>\n</head>\n'
                          '<body>\n{!s}\n</body>\n'
                          '</html>')

    def make_html(self):
        with open('index.html', 'w', encoding='utf-8') as f:
            text = self.HTML_TEMP.format(文件夹对象(self.path))
            f.write(text)


文件统计().make_html()
