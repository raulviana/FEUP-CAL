# Smart Delivery

## Authors

* Diogo Alexandre, up201706892@fe.up.pt, [GitHub](https://github.com/diogoalex01)

* Liliana Almeida, up201706908@fe.up.pt, [GitHub](https://github.com/lilianalmeida)

* Raul Viana, up201208089@fe.up.pt, [GitHub](https://github.com/raulviana)

------

## 1. Dependencies List

### 1.1. Input Files

To increase accuracy we used maps extracted from **OpenStreetMap**.

The following **Regions** were used:

* Aveiro
* Braga
* Coimbra
* Ermesinde
* Fafe
* Gondomar
* Lisboa
* Maia
* Porto
* Viseu

In the following formats:

#### 1.1.1. Nodes

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; T04_nodes_X_Y_**_Region_**.txt

#### 1.1.2. Edges

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; T04_edges_**_Region_**.txt


#### 1.1.3. Tags

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; T04_tags_**_Region_**.txt

#### 1.1.4. Deliveries

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; deliveries_**_Region_**.txt

### 1.2 API

* GraphViewerController.jar

### 1.3 Libraries

* connection.h
* graphviewer.h
* edgetype.h
* graph.h
* MutablePriorityQueue.h

-------

## 2. Instructions

> Due to compilation reasons, you must compile and run on Linux.

1. Clone the repository.

2. In project root, access 'Source'.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; _$ cd Source_

3. Execute command 'make' to compile.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; _$ make_

4. Run.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; _$ ./smartDelivery_
 
