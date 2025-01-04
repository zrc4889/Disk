import os 
from datetime import datetime
import time

def generate_html(path, root_path):
    # 获取目录内容
    items = []
    try:
        for item in os.listdir(path):
            if item == '.git' or item == '.github' :  # 排除.git文件夹
                continue
            full_path = os.path.join(path, item)
            mtime = os.path.getmtime(full_path)
            mod_time = datetime.fromtimestamp(mtime).strftime('%Y-%m-%d %H:%M:%S')
            is_dir = os.path.isdir(full_path)
            items.append((item, is_dir, mod_time))
    except Exception as e:
        print(f"Error reading directory {path}: {e}")
        return

    # 生成HTML内容
    html_content = f'''
    <html>
    <head>
        <title>CharonTree's World | Disk</title>
        <meta charset="utf-8">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css">
        <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600&display=swap" rel="stylesheet">
        <style>
            body {{ 
                font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif; 
                margin: 40px; 
                background-color: #f8f9fa; 
                color: #2c3e50;
                line-height: 1.6;
            }}
            table {{ 
                border-collapse: collapse; 
                width: 100%; 
                background-color: white; 
                box-shadow: 0 2px 4px rgba(0,0,0,0.1); 
                border-radius: 8px;
                overflow: hidden;
            }}
            th, td {{ 
                padding: 12px 15px; 
                text-align: left; 
                border-bottom: 1px solid #eee;
                font-size: 14px;
            }}
            th {{ 
                background-color: #f8f9fa; 
                font-weight: 600; 
                color: #444;
                text-transform: uppercase;
                font-size: 12px;
                letter-spacing: 0.5px;
            }}
            tr:hover {{ background-color: #f5f5f5; transition: background-color 0.2s; }}
            a {{ text-decoration: none; color: #2c3e50; }}
            a:hover {{ color: #007bff; }}
            .current-path {{ 
                margin-bottom: 30px; 
                background-color: white; 
                padding: 20px; 
                border-radius: 8px; 
                box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            }}
            .current-path h2 {{ 
                margin: 0 0 10px 0; 
                color: #2c3e50;
                font-weight: 600;
                font-size: 20px;
            }}
            i {{ margin-right: 12px; }}
            i.fa-folder {{ color: #ffd700; }}
            i.fa-file {{ color: #a9a9a9; }}
            i.fa-arrow-up {{ color: #007bff; }}
            .back-link {{ 
                display: inline-block; 
                padding: 8px 15px; 
                background-color: #f8f9fa; 
                border-radius: 6px;
                font-size: 14px;
                font-weight: 500;
            }}
            .back-link:hover {{ background-color: #e9ecef; }}
        </style>
    </head>
    <body>
        <div class="current-path">
            <h2>{path}</h2>
        </div>
        
        <table>
            <tr>
                <th>名称</th>
                <th>修改时间</th>
            </tr>
    '''
# 如果不是根目录，添加返回上级目录的行
    if path != root_path:
        html_content += f'''
                <tr onclick="window.location='../index.html'" style="cursor: pointer;">
                    <td style="width: 50%;"><i class="fas fa-folder"></i>..</td>
                    <td style="width: 30%;"></td>
                </tr>
        '''

# 其余的文件和文件夹列表代码保持不变

    # 添加文件和文件夹列表
    
    for item, is_dir, mod_time in sorted(items, key=lambda x: (-x[1], x[0].lower())):
        if item == "index.html":
            continue
        item_path = item if not is_dir else f"{item}/index.html"
        icon = 'fa-folder' if is_dir else 'fa-file'
        html_content += f'''
            <tr onclick="window.location='{item_path}'" style="cursor: pointer;">
                <td style="width: 50%;"><i class="fas {icon}"></i>{item}</td>
                <td style="width: 30%;">{mod_time}</td>
            </tr>
        '''
    
    # for item, is_dir, mod_time in sorted(items, key=lambda x: (-x[1], x[0].lower())):
    #     item_path = item if not is_dir else f"{item}/index.html"
    #     icon = 'fa-folder' if is_dir else 'fa-file'
    #     html_content += f'''
    #         <tr>
    #         <td style="width: 50%;"><a href="{item_path}"><i class="fas {icon}"></i>{item}</a></td>
    #         <td style="width: 30%;">{mod_time}</td>
    #         </tr>
    #     '''

        # html_content += '''
        # </table>
        # <div class="notice-board">
        #     <h3><i class="fas fa-bullhorn"></i> 公告栏</h3>
        #     <div class="notice-content">
        #     <p>欢迎使用文件浏览系统！</p>
        #     <p>这里可以添加重要通知和说明。</p>
        #     </div>
        # </div>
        # <style>
        #     .container {{ 
        #     display: flex; 
        #     gap: 20px;
        #     }}
        #     table {{ 
        #     flex: 1;
        #     margin-right: 20px;
        #     }}
        #     .notice-board {{ 
        #     width: 250px;
        #     background: white;
        #     padding: 20px;
        #     border-radius: 8px;
        #     box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        #     position: fixed;
        #     right: 40px;
        #     top: 40px;
        #     }}
        #     .notice-board h3 {{ 
        #     margin-top: 0;
        #     color: #2c3e50;
        #     font-size: 16px;
        #     border-bottom: 2px solid #eee;
        #     padding-bottom: 10px;
        #     }}
        #     .notice-board i {{ 
        #     color: #f39c12;
        #     }}
        #     .notice-content {{ 
        #     font-size: 14px;
        #     color: #666;
        #     }}
        # </style>
        # '''
    html_content += '''
        </table>
    </body>
    </html>
    '''


    # 保存HTML文件
    output_file = os.path.join(path, 'index.html')
    if 'workflow' in path: 
        return
    try:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(html_content)
    except Exception as e:
        print(f"Error writing file {output_file}: {e}")

def process_directory(start_path):
    # 获取绝对路径作为根路径
    root_path = os.path.abspath(start_path)
    
    # 处理当前目录
    generate_html(root_path, root_path)

    # 递归处理子目录
    for root, dirs, files in os.walk(root_path):
        if '.git' in dirs:
            dirs.remove('.git')  # 排除.git文件夹
        for dir_name in dirs:
            full_path = os.path.join(root, dir_name)
            generate_html(full_path, root_path)

if __name__ == '__main__':
    # 使用当前目录作为起始点
    start_path = '.'
    process_directory(start_path)
    print("目录浏览HTML文件生成完成！")
