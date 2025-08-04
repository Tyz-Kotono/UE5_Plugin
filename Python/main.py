import unreal
import sys
import os

# 导入Virtual Env QT，每个人的环境路径不同需要修改
sys.path.append(r"D:\Code\env313\Lib\site-packages")
from PySide6.QtWidgets import (
    QWidget,
    QApplication,
    QVBoxLayout,
    QLabel,
    QPushButton,
    QFileDialog,
    QInputDialog
)
from PySide6.QtCore import QSize

class QTWidget(QWidget):
    def __init__(self, parent=None):
        super(QTWidget, self).__init__(parent)
        self.setWindowTitle("QT Window")
        self.setFixedSize(300, 200)
        self.create()

    def create(self):
        layout = QVBoxLayout()
        button = QPushButton("导出贴图")
        button.clicked.connect(self.ExportTexture)
        layout.addWidget(button)
        self.setLayout(layout)

    def ExportTexture(self):
        import unreal

        # 获取选中的贴图资源
        selected_assets = unreal.EditorUtilityLibrary.get_selected_assets()
        if not selected_assets:
            unreal.log_warning("No assets selected!")
            return

        # 弹出文件夹选择对话框
        folder_path = QFileDialog.getExistingDirectory(
            self,
            "Select Export Folder",
            "",
            QFileDialog.ShowDirsOnly | QFileDialog.DontResolveSymlinks
        )

        if not folder_path:
            return

        # 支持的贴图格式和对应的导出器
        supported_formats = {
            "png": unreal.TextureExporterPNG(),
            "tga": unreal.TextureExporterTGA(),
            "exr": unreal.TextureExporterEXR(),
            "hdr": unreal.TextureExporterHDR()
        }

        # 让用户选择格式
        format, ok = QInputDialog.getItem(
            self,
            "Export Format",
            "Select texture format:",
            list(supported_formats.keys()),
            0,
            False
        )

        if not ok:
            return

        # 创建导出任务
        export_task = unreal.AssetExportTask()
        export_task.automated = True
        export_task.replace_identical = True
        export_task.exporter = supported_formats[format]

        # 批量导出选中的贴图
        success_count = 0
        with unreal.ScopedSlowTask(len(selected_assets), "Exporting Textures...") as slow_task:
            slow_task.make_dialog(True)

            for asset in selected_assets:
                if not isinstance(asset, unreal.Texture):
                    unreal.log_warning(f"Skipped {asset.get_name()} - Not a texture")
                    continue

                slow_task.enter_progress_frame(1, f"Exporting {asset.get_name()}")

                # 设置导出路径
                export_task.filename = f"{folder_path}/{asset.get_name()}.{format}"
                export_task.object = asset

                # 执行导出
                if unreal.Exporter.run_asset_export_task(export_task):
                    unreal.log(f"Successfully exported: {export_task.filename}")
                    success_count += 1
                else:
                    unreal.log_error(f"Failed to export: {asset.get_name()}")

        # 显示完成通知
        unreal.EditorDialog.show_message(
            "Export Complete",
            f"Exported {success_count}/{len(selected_assets)} textures",
            unreal.AppMsgType.OK
        )



if __name__ == "__main__":
    app = None
    if not QApplication.instance():
        app = QApplication(sys.argv)

    window = QTWidget()
    window.show()
    # QT 嵌入slate
    unreal.parent_external_window_to_slate(window.winId())