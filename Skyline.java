import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStream;
import java.util.*;
import java.io.*;
import java.awt.geom.*;
import java.lang.*;
import javafx.util.*;

public class Main {
  public static void main(String[] args) {
    
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    TaskJ solver = new TaskJ();
    solver.solve(1, in, out);
    out.close();
  }

  static class TaskJ {
    public void solve(int testNumber, InputReader in, PrintWriter out) {
      int n = in.nextInt();
      
      double[][] a = new double[n][8];
      TreeSet<Integer> S = new TreeSet<Integer>();
      double[] visible = new double[n];
      for (int i = 0; i < n; i++) {
        int x1 = in.nextInt();
        int y1 = in.nextInt();
        int x2 = in.nextInt();
        int y2 = in.nextInt();
        double [] pts = new double[8];
        pts[0] = x1; pts[1] = 0;
        pts[2] = x2; pts[3] = 0;
        pts[4] = x2; pts[5] = y2;
        pts[6] = x1; pts[7] = y1;
        a[i] = pts;
        S.add(x1);
        S.add(x2);
        visible[i] = 0;
      }
      Object[] cx = S.toArray();
      for (int i = 0; i < cx.length-1; i++) {
        Area[] v =  new Area[n];
        for (int j = 0; j < n; j++) {
          double [] pts = a[j].clone();
          pts[0] = Math.max((double)(int)cx[i], pts[0]);
          pts[2] = Math.min((double)(int)cx[i+1], pts[2]);
          pts[4] = Math.min((double)(int)cx[i+1], pts[4]);
          pts[6] = Math.max((double)(int)cx[i], pts[6]);
          v[j] = new Area();
          if (pts[0] >= pts[2]) continue;
          double t1 = (pts[0]-a[j][0])/(a[j][2]-a[j][0]);
          double t2 = (pts[2]-a[j][0])/(a[j][2]-a[j][0]);
          pts[5] = a[j][7] + t1*(a[j][5] - a[j][7]);
          pts[7] = a[j][7] + t2*(a[j][5] - a[j][7]);
          v[j] = AWT.makeArea(pts);
        }
        Area u = new Area();
        for (int j = 0; j < n; j++) {
          if (v[j].isEmpty()) continue;
          Area x = (Area)v[j].clone();
          x.subtract(u);
          visible[j] += AWT.computeArea(x);
          u.add(x);
        }
      }
      for (int j = 0; j < n; j++) {
        out.printf("%.8f\n", visible[j]/AWT.computeArea(AWT.makeArea(a[j])));
      }
    }
  }

  static class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;
    public InputReader(InputStream stream) {
      reader = new BufferedReader(new InputStreamReader(stream), 32768);
      tokenizer = null;
    }
    public String next() {
      while (tokenizer == null || !tokenizer.hasMoreTokens()) {
        try {
          tokenizer = new StringTokenizer(reader.readLine());
        } catch (IOException e) {
          throw new RuntimeException(e);
        }
      }
      return tokenizer.nextToken();
    }
    public int nextInt() {
      return Integer.parseInt(next());
    }
  }
}


class AWT{
  static Area makeArea(double[] pts){
    Path2D.Double p = new Path2D.Double();
    p.moveTo(pts[0], pts[1]);
    for(int i = 2; i < pts.length; i+=2){
      p.lineTo(pts[i], pts[i+1]);
    }
    p.closePath();
    return new Area(p);
  }
  static double computePolygonArea(ArrayList<Point2D.Double> points) {
    Point2D.Double[] pts = points.toArray(new Point2D.Double[points.size()]);  
    double area = 0;
    for (int i = 0; i < pts.length; i++){
      int j = (i+1) % pts.length;
      area += pts[i].x * pts[j].y - pts[j].x * pts[i].y;
    }        
    return Math.abs(area)/2;
  }
  static double computeArea(Area area) {
    double totArea = 0;
    PathIterator iter = area.getPathIterator(null);
    ArrayList<Point2D.Double> points = new ArrayList<Point2D.Double>();
    while (!iter.isDone()) {
      double[] buffer = new double[6];
      switch (iter.currentSegment(buffer)) {
        case PathIterator.SEG_MOVETO:
        case PathIterator.SEG_LINETO:
          points.add(new Point2D.Double(buffer[0], buffer[1]));
          break;
        case PathIterator.SEG_CLOSE:
          totArea += computePolygonArea(points);
          points.clear();
          break;
      }
      iter.next();
    }
    return totArea;
  }
}
