

# 1. 背景
There are multiple benefits of integrating Jupyter Notebooks in Kubeflow for enterprise environments. These benefits include:

* Integrating well with the rest of the infrastructure with respect to authentication and access control.

* Enabling easier notebook sharing across the organization.
    * Enabling easier notebook sharing across the organization.
    * Users can create notebook containers or pods directly in the cluster, rather than locally on their workstations. 
    * Admins can provide standard notebook images for their organization, and set up role-based access control (RBAC), Secrets and Credentials to manage which teams and individuals can access the notebooks.

# 2. 特点
* When you bundle Jupyter Notebooks in Kubeflow, you can use the Fairing library to submit training jobs using TFJob. 
* The training job can run single node or distributed on the same Kubernetes cluster, but not inside the notebook pod itself. （notebook运行在一个pod中）


