#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import argparse


def main(fgraph, fpath):

    def make_tuple(l):
        s = l.strip().split("\t")[1].replace("(","").replace(")","")
        p = s.split(", ")
        return tuple(map(float, p))

    clean = lambda s: s.split("/")[-1].replace(".","_")
    plotname = "{0}+{1}".format(clean(fgraph.name),clean(fpath.name))


    path = np.loadtxt(fpath, dtype='float')
    pxs,pys = path[:,0],path[:,1]

    graph = [make_tuple(l) for l in fgraph]
    gxs = [gp[0] for gp in graph]
    gys = [gp[1] for gp in graph]


    fig = plt.figure(1)
    fig.set_size_inches(fig.get_figwidth(), fig.get_figwidth())
    plt.scatter(gxs, gys, c='r')
    plt.plot(pxs, pys, c='r', alpha=0.4)
    plt.savefig(plotname)
    plt.close()


    fgraph.close()
    fpath.close()
    return

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Plot a random walk on Sierpinski Gasket.",
        epilog="Made with love and cleverness by Andy C."
    )
    parser.add_argument('fgraph',
                        metavar='graph-file',
                        type=argparse.FileType('r'),
                        help=".output file containing graph data.")
    parser.add_argument('fpath',
                        metavar='path-file',
                        type=argparse.FileType('r'),
                        help=".output file containing path data.")
    args = parser.parse_args()
    main(args.fgraph, args.fpath)
