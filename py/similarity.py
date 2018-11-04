
from PyQt5 import QtWidgets, QtGui, QtCore

import sys, os
import filecmp
import send2trash
import imageio
import cv2
import numpy as np

import time

from multiprocessing import Pool

import configparser
import argparse


IMG_EXT = [".png", ".jpg", ".jpeg"]
GIF_EXT = [".gif"]
MOV_EXT = [".mp4", ".avi"]


def imgToQImage(im, w, h):
    return QtGui.QImage(im.data, im.shape[1], im.shape[0], im.strides[0], QtGui.QImage.Format_RGB888).scaled(w, h, QtCore.Qt.KeepAspectRatio)



class QFFMPEGMovie(QtGui.QImageReader):
    def __init__(self, label, movPath, Nimages=500):
        QtGui.QImageReader.__init__(self)
        self.label = label

        self.vid = imageio.get_reader(movPath, "avbin")    #'ffmpeg'
        #print self.vid.get_meta_data()
        self.fps = self.vid.get_meta_data()["fps"]
        self.period_ms = 1000.0/self.fps
        self.realW, self.realH = self.vid.get_meta_data()["size"]
        self.nframes = min(self.vid.get_meta_data()["nframes"], Nimages)

        self.index = 0
        self.show(self.index)
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.showNext)


    def getOriginalSize(self):
        return self.realW, self.realH

    def showNext(self):
        self.index = (self.index+1)%self.nframes
        #t = time.clock() - self.t0
        #self.index = (int(t*self.fps))%self.nframes
        self.show(self.index)

    def show(self, idx):
        if self.nframes:
            w, h = self.label.width(), self.label.height()
            self.label.setPixmap(QtGui.QPixmap(imgToQImage(self.vid.get_data(idx), w, h)))

    def start(self):
        self.t0 = time.clock()
        self.timer.start(self.period_ms)

    def stop(self):
        self.timer.stop()
        self.vid.close()


class VLine(QtWidgets.QFrame):
    def __init__(self):
        QtWidgets.QFrame.__init__(self)
        self.setFrameShape(QtWidgets.QFrame.VLine)
        self.setFrameShadow(QtWidgets.QFrame.Sunken)


class FolderSelecterWidget(QtWidgets.QWidget):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        layout = QtWidgets.QHBoxLayout()
        self.setLayout(layout)

        self.edit = QtWidgets.QLineEdit()
        self.browseBtn = QtWidgets.QPushButton("browse")

        self.browseBtn.clicked.connect(self.browseBtn_clicked)

        layout.addWidget(self.edit)
        layout.addWidget(self.browseBtn)

        user_root_path = os.environ["USERPROFILE"] if os.name=="nt" else os.environ["HOME"]
        self.edit.setText(user_root_path)

    def getFolder(self):
        return str(self.edit.text())

    def browseBtn_clicked(self):
        res = QtWidgets.QFileDialog.getExistingDirectory(
            self,
            "select folder",
            str(self.edit.text())
        )
        res = str(res)
        if len(res)==0:
            return
        else:
            self.edit.setText(res)



class OptionSelecterWidget(QtWidgets.QWidget):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        layout = QtWidgets.QHBoxLayout()
        self.setLayout(layout)

        self.options = {}
        layout.addStretch()
        for n, l, c in [("bytecomp", "byte comp", True), ("histo", "histogram comp", False), ("gifhisto", "gif histogram comp", False)]:
            w = QtWidgets.QCheckBox(l)
            self.options[n] = w
            w.setChecked(c)
            layout.addWidget(w)
        layout.addStretch()

    def getOptions(self):
        options = {}
        for k,v in self.options.items():
            options[k] = v.isChecked()
        return options




class QGIFMovie(QtGui.QImageReader):
    def __init__(self, label, movPath):
        QtGui.QImageReader.__init__(self)
        self.label = label

        shape = imageio.mimread(movPath)[0].shape
        self.realH, self.realW = shape[0], shape[1]  #careful: inversion

        self.vid = QtGui.QMovie(movPath)
        self.vid.frameChanged.connect(self.updatePixmap)

    def getOriginalSize(self):
        return self.realW, self.realH

    def updatePixmap(self):
        w, h = self.label.width(), self.label.height()
        self.label.setPixmap(self.vid.currentPixmap().scaled(w, h, QtCore.Qt.KeepAspectRatio))

    def start(self):
        self.vid.start()

    def stop(self):
        self.vid.stop()




class ImageViewerWidget(QtWidgets.QLabel):
    def __init__(self, *args, **kwargs):
        QtWidgets.QLabel.__init__(self, *args, **kwargs)
        self.original_pixmap = QtGui.QPixmap()

    def getOriginalSize(self):
        return self.original_pixmap.width(), self.original_pixmap.height()

    def setImage(self, imgPath):
        image_reader = QtGui.QImageReader()
        image_reader.setDecideFormatFromContent(True)
        image_reader.setFileName(imgPath)
        self.original_pixmap = QtGui.QPixmap.fromImageReader(image_reader)
        self.displayImage()

    def displayImage(self):
        self.setPixmap(self.original_pixmap.scaled(self.width(), self.height(), QtCore.Qt.KeepAspectRatio))

    def resizeEvent(self, event):
        self.displayImage()




class ImgDisplayerWidget(QtWidgets.QWidget):
    def __init__(self, w, h):
        QtWidgets.QWidget.__init__(self)
        layout = QtWidgets.QVBoxLayout()
        self.setLayout(layout)
        self.action = None
        self.movie = None
        self.imgPath = ""
        self.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)

        self.indicator = QtWidgets.QLabel("...", alignment=QtCore.Qt.AlignHCenter)
        self.indicator.setTextInteractionFlags(QtCore.Qt.TextSelectableByMouse)
        self.indicator.setSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Minimum)

        self.img = ImageViewerWidget(alignment=QtCore.Qt.AlignHCenter|QtCore.Qt.AlignVCenter)
        self.img.setMinimumSize(w, h)
        self.img.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)

        self.delBtn = QtWidgets.QPushButton("delete")
        self.delBtn.clicked.connect(self.delBtn_clicked)

        layout.addWidget(self.indicator, alignment=QtCore.Qt.AlignHCenter)
        layout.addWidget(self.img)
        layout.addWidget(self.delBtn, alignment=QtCore.Qt.AlignHCenter)


    def delBtn_clicked(self):
        self.clearPixmapMovie()
        print("delete %s" % self.indicator.text())
        send2trash.send2trash(self.imgPath)
        self.action(self.imgPath)

    def setDeleteAction(self, action):
        self.action = action

    def clearPixmapMovie(self):
        self.img.setPixmap(QtGui.QPixmap())
        if self.movie is not None:
            self.movie.stop()
        self.movie = None
        self.img.setMovie(QtGui.QMovie())

    def clearImg(self):
        self.imgPath = ""
        self.indicator.setText("...")
        self.img.setText(".")
        self.clearPixmapMovie()

    def setImg(self, imgPath):
        self.clearImg()
        self.imgPath = imgPath
        ext = os.path.splitext(imgPath)[1]

        if ext in IMG_EXT:
            self.img.setImage(imgPath)
            w,h = self.img.getOriginalSize()

        elif ext in GIF_EXT:
            self.movie = QGIFMovie(self.img, imgPath)
            self.movie.start()
            w, h = self.movie.getOriginalSize()

        elif ext in MOV_EXT:
            self.movie = QFFMPEGMovie(self.img, imgPath)
            self.movie.start()
            w, h = self.movie.getOriginalSize()
        else:
            w,h = 0,0

        self.indicator.setText("{0} [{w}x{h} {1:.2f}Mo]".format(imgPath, os.path.getsize(imgPath)*1e-6, w=w, h=h))









class ComparisonDisplayerWidget(QtWidgets.QWidget):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        layout = QtWidgets.QVBoxLayout()
        self.setLayout(layout)
        self.index = 0

        self.indicator = QtWidgets.QLabel(alignment=QtCore.Qt.AlignHCenter)
        hlayout = QtWidgets.QHBoxLayout()

        layout.addWidget(self.indicator, alignment=QtCore.Qt.AlignHCenter|QtCore.Qt.AlignVCenter)
        layout.addLayout(hlayout)

        self.backBtn = QtWidgets.QPushButton("<<<")
        self.backBtn.setSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.leftImg  = ImgDisplayerWidget(400,400)
        self.rightImg = ImgDisplayerWidget(400,400)
        self.nextBtn = QtWidgets.QPushButton(">>>")
        self.nextBtn.setSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)

        self.backBtn.clicked.connect(self.displayBack)
        self.nextBtn.clicked.connect(self.displayNext)

        hlayout.addWidget(self.backBtn)
        hlayout.addWidget(self.leftImg)
        hlayout.addWidget(VLine())
        hlayout.addWidget(self.rightImg)
        hlayout.addWidget(self.nextBtn)

        self.leftImg.setDeleteAction(self.deleteAction)
        self.rightImg.setDeleteAction(self.deleteAction)

        self.setPairs([])


    def setPairs(self, pairs):
        self.pairs = pairs

        self.index = 0
        self.displayPair(0)


    def displayBack(self):
        self.index -= 1
        self.displayPair(self.index)

    def displayNext(self):
        self.index += 1
        self.displayPair(self.index)

    def displayPair(self, idx):
        if len(self.pairs) == 0:
            self.indicator.setText("0/0")
            self.leftImg.clearImg()
            self.rightImg.clearImg()
            return

        self.index = idx
        if self.index < 0:
            self.index = 0
        if self.index > len(self.pairs)-1:
            self.index = len(self.pairs)-1

        self.indicator.setText("{0}/{1}".format(self.index+1, len(self.pairs)))
        self.setEnablingButton()

        lf, rf = self.pairs[self.index]
        self.leftImg.setImg(lf)
        self.rightImg.setImg(rf)

    def setEnablingButton(self):
        self.backBtn.setEnabled(0 < self.index)
        self.nextBtn.setEnabled(self.index+1 < len(self.pairs))


    def deleteAction(self, imgPath):
        l_img, r_img = self.pairs[self.index]
        assert( imgPath == l_img or imgPath == r_img)
        substitute  = l_img if imgPath == r_img else r_img

        for idx, p  in enumerate(self.pairs):
            if p[0] == imgPath:
                self.pairs[idx] = (substitute, p[1])
            if p[1] == imgPath:
                self.pairs[idx] = (p[0], substitute)

        self.pairs.pop(self.index)
        self.displayPair(self.index)





def getMinimalSetOfPairs(pairs):
    spairs = [tuple(sorted(p)) for p in pairs]
    return list(set(spairs))


def runExtractionOfAllSimilarPairs(folderPath, options=None, progressbar=None):
    files = [os.path.join(folderPath, f) for f in os.listdir(folderPath)]
    files = [f for f in files if os.path.isfile(f)]

    pairs = []
    if options is None or ("bytecomp" in options and options["bytecomp"] == True):
        pairs += getByteComparisonPairs(files, progressbar)
    if options is None or ("histo" in options and options["histo"] == True):
        pairs += getHistogramComparisonPairs(files, progressbar)
    if options is None or ("gifhisto" in options and options["gifhisto"] == True):
        pairs += getGIFHistogramComparisonPairs(files, progressbar)

    pairs = getMinimalSetOfPairs(pairs)
    return pairs

def getByteComparisonPairs(files, progressbar=None):
    print("==================== getByteComparisonPairs")
    if progressbar is not None: progressbar.setLabel("Byte Comparison:")
    t0 = time.clock()
    wFiles = [(os.path.getsize(ff), ff) for ff in files]
    wFiles.sort()
    pairs = []

    Ntotal = (len(wFiles)-1)**2
    idx = 0
    for f0, f1 in zip(wFiles[0:-1], wFiles[1:]):
        if f0[0] == f1[0]:
            pairs.append((f0[1], f1[1]))
            idx+=1
            if progressbar is not None:
                progressbar.setValue(idx*100.0/Ntotal)

    pairs = [(f0, f1) for f0, f1 in pairs if filecmp.cmp(f0,f1)]
    T = time.clock() - t0
    print("%s %s" % (T, len(pairs)))
    return pairs



def _computeHisto(ff):
    img = cv2.imread(ff)
    if img is not None:
        histograms = [cv2.calcHist([img],[idxj],None,[256],[0,256]) for idxj in range(3)]
        return (histograms, ff)
    else:
        return None



def _computeGIFHisto(gifff):
    gif = imageio.mimread(gifff)
    if gif is not None and len(gif):
        img0 = gif[0]
        if len(img0.shape) == 2: #greyscale
            img = cv2.cvtColor(img0, cv2.COLOR_GRAY2BGR)
        else:
            img0 = img0[:,:,:3]   # to remove alpha channel if any
            img = cv2.cvtColor(img0, cv2.COLOR_RGB2BGR)
        histograms = [cv2.calcHist([img],[idxj],None,[256],[0,256]) for idxj in range(3)]
        return (histograms, gifff)
    else:
        return None

def _compareHisto(data):
    h0, h1, cmpType, moreThan, threshold = data[0][0], data[1][0], data[2], data[3], data[4]
    res = np.array([cv2.compareHist(h0[i], h1[i], cmpType) for i in range(3)])
    if moreThan and (res >= threshold).all():
            return data[0][1], data[1][1]
    elif not moreThan and (res <= threshold).all():
        return data[0][1], data[1][1]
    else:
        return None


def getHistogramComparisonPairs(files, progressbar=None):
    print("==================== getHistogramComparisonPairs")
    if progressbar is not None: progressbar.setLabel("Histogram Comparison:")
    pool = Pool(processes=8)
    t0 = time.clock()
    print("=== load images")
    if progressbar is not None: progressbar.setLabel("Histogram Comparison: Load images")
    progressbar.setValue(0.0)
    images = [ff for ff in files if os.path.splitext(ff)[1] in IMG_EXT]

    #hfiles = pool.map(_computeHisto, images)
    hfiles = []
    Ntotal = len(images)
    N = 100
    for idx in range(int(Ntotal/N) + 1):
        hfiles.extend(pool.map(_computeHisto, images[N*idx:N*(idx+1)]))
        if progressbar is not None:
                progressbar.setValue(idx*N*100.0/Ntotal)

    hfiles = [h for h in hfiles if h is not None]
    T = time.clock() - t0
    print("%s %s" % (T, len(hfiles)))

    print("=== create pairs")
    if progressbar is not None: progressbar.setLabel("Histogram Comparison: create pairs")
    t0 = time.clock()
    pairsToTest = []
    Ntotal = len(hfiles)-1
    for idxi in range(0, len(hfiles)-1):
        for idxj in range(idxi+1, len(hfiles)):
            #pairsToTest.append((hfiles[idxi], hfiles[idxj], cv2.HISTCMP_CORREL, True, 0.99))
            pairsToTest.append((hfiles[idxi], hfiles[idxj], cv2.HISTCMP_BHATTACHARYYA, False, 0.14))
            if progressbar is not None:
                progressbar.setValue(idxi*100.0/Ntotal)

    T = time.clock() - t0
    print("%s %s" % (T, len(pairsToTest)))

    print("=== comparison")
    if progressbar is not None: progressbar.setLabel("Histogram Comparison: compare")
    t0 = time.clock()

    #pairs = pool.map(_compareHisto, pairsToTest)
    pairs = []
    Ntotal = len(pairsToTest)
    N = 100000
    if Ntotal>0:
        for idx in range(int(Ntotal/N) + 1):
            pairs.extend(pool.map(_compareHisto, pairsToTest[N*idx:N*(idx+1)]))
            if progressbar is not None:
                    progressbar.setValue(idx*N*100.0/Ntotal)


    pairs = [p for p in pairs if p is not None]
    T = time.clock() - t0
    print("%s %s" % (T, len(pairs)))

    return pairs




def getGIFHistogramComparisonPairs(files, progressbar=None):
    print("==================== getGIFHistogramComparisonPairs")
    if progressbar is not None: progressbar.setLabel("GIF Histogram Comparison:")
    pool = Pool(processes=8)
    t0 = time.clock()
    print("=== load images")
    if progressbar is not None: progressbar.setLabel("GIF Histogram Comparison: Load images")
    progressbar.setValue(0.0)
    #images = [ff for ff in files if os.path.splitext(ff)[1] in IMG_EXT]
    gifimages = [ff for ff in files if os.path.splitext(ff)[1] in GIF_EXT]

    #hfiles = pool.map(_computeGIFHisto, gifimages)
    hfiles = []
    Ntotal = len(gifimages)
    N = 50
    for idx in range(int(Ntotal/N) + 1):
        hfiles.extend(pool.map(_computeGIFHisto, gifimages[N*idx:N*(idx+1)]))
        if progressbar is not None:
                progressbar.setValue(idx*N*100.0/Ntotal)

    hfiles = [h for h in hfiles if h is not None]
    T = time.clock() - t0
    print("%s %s" % (T, len(hfiles)))

    print("=== create pairs")
    if progressbar is not None: progressbar.setLabel("GIF Histogram Comparison: create pairs")
    t0 = time.clock()
    pairsToTest = []
    Ntotal = len(hfiles)-1
    for idxi in range(0, len(hfiles)-1):
        for idxj in range(idxi+1, len(hfiles)):
            #pairsToTest.append((hfiles[idxi], hfiles[idxj], cv2.HISTCMP_CORREL, True, 0.99))
            pairsToTest.append((hfiles[idxi], hfiles[idxj], cv2.HISTCMP_BHATTACHARYYA, False, 0.14))
            if progressbar is not None:
                progressbar.setValue(idxi*100.0/Ntotal)

    T = time.clock() - t0
    print("%s %s" % (T, len(pairsToTest)))

    print("=== comparison")
    if progressbar is not None: progressbar.setLabel("GIF Histogram Comparison: compare")
    t0 = time.clock()

    #pairs = pool.map(_compareHisto, pairsToTest)
    pairs = []
    Ntotal = len(pairsToTest)
    N = 100000
    if Ntotal>0:
        for idx in range(int(Ntotal/N) + 1):
            pairs.extend(pool.map(_compareHisto, pairsToTest[N*idx:N*(idx+1)]))
            if progressbar is not None:
                    progressbar.setValue(idx*N*100.0/Ntotal)


    pairs = [p for p in pairs if p is not None]
    T = time.clock() - t0
    print("%s %s" % (T, len(pairs)))

    return pairs





class ComputePairsThread(QtCore.QThread):

    finished = QtCore.pyqtSignal(object)

    def __init__(self, parent, folderPath, options, progressbar):
        QtCore.QThread.__init__(self, parent)
        self.folderPath = folderPath
        self.options = options
        self.progressbar = progressbar



    def run(self):
        pairs = runExtractionOfAllSimilarPairs(self.folderPath, self.options, self.progressbar)
        self.finished.emit(pairs)






class TitledProgressBar(QtWidgets.QWidget):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        layout = QtWidgets.QVBoxLayout()
        self.setLayout(layout)

        self.label = QtWidgets.QLabel()
        self.label.setMinimumWidth(300)
        self.progressBar = QtWidgets.QProgressBar()
        self.progressBar.setMinimumWidth(300)

        layout.addWidget(self.label)
        layout.addWidget(self.progressBar)
        #layout.setContentsMargins(0,0,0,0)

    def setLabel(self, label):
        self.label.setText(label)

    def setValue(self, value):
        self.progressBar.setValue(value)





class SimilarCheckerWidget(QtWidgets.QWidget):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        layout = QtWidgets.QVBoxLayout()
        self.setLayout(layout)

        self.folderSelecter = FolderSelecterWidget()
        self.optionSelecter = OptionSelecterWidget()
        self.startBtn = QtWidgets.QPushButton("start")
        self.comparisonDisplayer= ComparisonDisplayerWidget()

        layout.addWidget(self.folderSelecter)
        layout.addWidget(self.startBtn)
        layout.addWidget(self.optionSelecter)
        layout.addWidget(self.comparisonDisplayer)

        self.progressBar = TitledProgressBar()

        #self.folderSelecter.setAction(self.processFolder)
        self.startBtn.clicked.connect(self.processFolder)


    def processFolder(self):
        folderPath = self.folderSelecter.getFolder()
        options = self.optionSelecter.getOptions()

        self.computePairsThread = ComputePairsThread(self, folderPath, options, self.progressBar)
        self.computePairsThread.finished.connect(self.processFolderFinished)
        self.computePairsThread.start()
        self.progressBar.show()


    def processFolderFinished(self, pairs):
        self.comparisonDisplayer.setPairs(pairs)
        self.progressBar.close()
        if len(pairs)==0:
            QtWidgets.QMessageBox.information(self, "Result", "no similar files found")


def parseConfigFile(cfgFilePath):
    if cfgFilePath and os.path.exists(cfgFilePath):
        with open(cfgFilePath, 'r') as f:
            config_string = '[section]\n' + f.read()
        config = configparser.ConfigParser()
        #config.read_string(unicode(config_string))
        config.read_string(config_string)
        return config["section"]
    else:
        return {}



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Similar file checker', formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('-c', '--config', type=str, default="similarity.conf", help='config file to initialize program')
    parser.add_argument('-i', "--init_folder")
    args = parser.parse_args()

    configparam = parseConfigFile(args.config)
    init_folder =  os.getcwd()
    if "init_folder" in configparam:
        init_folder = configparam["init_folder"]
    if args.init_folder is not None:
        init_folder = args.init_folder


    app = QtWidgets.QApplication(sys.argv)
    w = SimilarCheckerWidget()
    w.move(50,50)
    w.folderSelecter.edit.setText(init_folder)
    w.showMaximized()
    res = app.exec_()

