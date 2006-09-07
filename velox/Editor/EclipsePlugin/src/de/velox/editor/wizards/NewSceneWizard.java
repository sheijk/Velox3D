/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * Eclipse Public Licence 1.0. See licence_epl.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_epl.txt for the
 * complete licence text
 */

package de.velox.editor.wizards;

import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;
import org.eclipse.core.runtime.*;
import org.eclipse.jface.operation.*;
import java.lang.reflect.InvocationTargetException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.core.resources.*;
import org.eclipse.core.runtime.CoreException;
import java.io.*;
import org.eclipse.ui.*;
import org.eclipse.ui.ide.IDE;

/**
 * This is a sample new wizard. Its role is to create a new file 
 * resource in the provided container. If the container resource
 * (a folder or a project) is selected in the workspace 
 * when the wizard is opened, it will accept it as the target
 * container. The wizard creates one file with the extension
 * "v3dscene". If a sample multi-page editor (also available
 * as a template) is registered for the same extension, it will
 * be able to open it.
 */

public class NewSceneWizard extends Wizard implements INewWizard {
	private NewSceneWizardPage page;
	private ISelection selection;
	private String fileName = null;
	
	/**
	 * Constructor for NewSceneWizard.
	 */
	public NewSceneWizard() {
		super();
		setNeedsProgressMonitor(true);
	}
	
	/**
	 * Adding the page to the wizard.
	 */

	public void addPages() {
		page = new NewSceneWizardPage(selection);
		addPage(page);
	}

	/**
	 * This method is called when 'Finish' button is pressed in
	 * the wizard. We will create an operation and run it
	 * using wizard as execution context.
	 */
	public boolean performFinish() {
		final String containerName = page.getContainerName();
		fileName = page.getFileName();
		
		IRunnableWithProgress op = new IRunnableWithProgress() {
			public void run(IProgressMonitor monitor) throws InvocationTargetException {
				try {
					doFinish(containerName, fileName, monitor);
				} catch (CoreException e) {
					throw new InvocationTargetException(e);
				} finally {
					monitor.done();
				}
			}
		};
		try {
			getContainer().run(true, false, op);
		} catch (InterruptedException e) {
			return false;
		} catch (InvocationTargetException e) {
			Throwable realException = e.getTargetException();
			MessageDialog.openError(getShell(), "Error", realException.getMessage());
			return false;
		}
		return true;
	}
	
	/**
	 * The worker method. It will find the container, create the
	 * file if missing or just replace its contents, and open
	 * the editor on the newly created file.
	 */

	private void doFinish(
		String containerName,
		String fileName,
		IProgressMonitor monitor)
		throws CoreException {
		// create a sample file
		monitor.beginTask("Creating " + fileName, 2);
		IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		IResource resource = root.findMember(new Path(containerName));
		if (!resource.exists() || !(resource instanceof IContainer)) {
			throwCoreException("Container \"" + containerName + "\" does not exist.");
		}
		IContainer container = (IContainer) resource;
		final IFile file = container.getFile(new Path(fileName));
		try {
			InputStream stream = openContentStream();
			if (file.exists()) {
				file.setContents(stream, true, true, monitor);
			} else {
				file.create(stream, true, monitor);
			}
			stream.close();
		} catch (IOException e) {
		}
		monitor.worked(1);
		monitor.setTaskName("Opening file for editing...");
		getShell().getDisplay().asyncExec(new Runnable() {
			public void run() {
				IWorkbenchPage page =
					PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
				try {
					IDE.openEditor(page, file, true);
				} catch (PartInitException e) {
				}
			}
		});
		monitor.worked(1);
	}
	
	/**
	 * We will initialize file contents with a sample text.
	 */

	private InputStream openContentStream() {
		try {
			final String sceneName = fileName.replaceAll("\\..*", "");
		
			final String contents =
				"<entity name=\"" + sceneName + "\">\n" + 
				"	<part type=\"v3d::scene::VNaiveSceneManagerPart\"/>\n" + 
				"	<part type=\"shooting\"/>\n" + 
				"	<part type=\"v3d::entity::VUpdateManagerPart\"/>\n" + 
				"	<part type=\"v3d::scene::VNaiveLightManager\"/>\n" +
				"	<part type=\"v3d::utils::VInputPart\" tags=\"\"/>\n" + 
				"	<entity name=\"editorCam\">\n" + 
				"		<part type=\"v3d::entity::VRigidBodyPart\" pos=\"(0,0,5)\" updir=\"(0,1,0)\" viewdir=\"(0,0,-1)\" tags=\"\"/>\n" + 
				"		<part type=\"v3d::utils::VCameraPart\" tags=\"\"/>\n" + 
				"		<part type=\"v3d::utils::VTrackballPart\" tags=\"\"/>\n" + 
				"	</entity>\n" + 
				"	<entity name=\"debug\">\n" + 
				"		<part type=\"v3d::entity::VRigidBodyPart\" pos=\"(0,0,0)\" updir=\"(0,1,0)\" viewdir=\"(0,0,1)\" tags=\"\"/>\n" + 
				"		<part type=\"v3d::scene::VOrientationGridPart\" material=\"/system/graphics/defaultMaterial\" tags=\"\"/>\n" + 
				"	</entity>\n" + 
				"</entity>\n" + 
				"";
			return new ByteArrayInputStream(contents.getBytes());
		}
		catch(RuntimeException e) {
			throw e;
		}
	}

	private void throwCoreException(String message) throws CoreException {
		IStatus status =
			new Status(IStatus.ERROR, "VeloxEditor", IStatus.OK, message, null);
		throw new CoreException(status);
	}

	/**
	 * We will accept the selection in the workbench to see if
	 * we can initialize from it.
	 * @see IWorkbenchWizard#init(IWorkbench, IStructuredSelection)
	 */
	public void init(IWorkbench workbench, IStructuredSelection selection) {
		this.selection = selection;
	}
}
